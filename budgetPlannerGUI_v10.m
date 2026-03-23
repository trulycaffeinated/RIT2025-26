function budgetPlannerGUI_v10()
% budgetPlannerGUI_v10
% Clean rebuild (syntax-safe) with:
% - Budget sliders + numeric fields
% - Expandable Utilities Breakdown using uitable (scroll wheel + scrollbars)
% - Expandable Vehicle Payment calculator and Apply to budget row
% - No forced FontColor styling (uses MATLAB defaults)
%
% Run:
%   budgetPlannerGUI_v10

    % ---- Config ----
    items = { ...
        'Nelnet Loan',         'Needs',   180; ...
        'FAFSA',               'Needs',   200; ...
        'Rent',                'Needs',  2400; ...
        'Utilities',           'Needs',   200; ...
        'Auto Insurance',      'Needs',   200; ...
        'Dining Out / Coffee', 'Wants',   300; ...
        'Subscriptions',       'Wants',    60; ...
        'Retirement',          'Savings', 720; ...
        'Emergency Fund',      'Savings', 300; ...
        'Short Term',          'Savings', 180; ...
        'Vehicle Payment',     'Needs',   350 ...
    };

    n = size(items,1);
    defaults = cell2mat(items(:,3));

    idxUtilities = find(strcmp(items(:,1),'Utilities'),1);
    if isempty(idxUtilities), idxUtilities = 4; end

    idxVehicle = find(strcmp(items(:,1),'Vehicle Payment'),1);
    if isempty(idxVehicle), idxVehicle = n; end

    % ---- UI ----
    f = uifigure('Name','Budget Planner','Position',[100 100 1100 760]);

    root = uigridlayout(f,[2 1]);
    root.RowHeight = {60,'1x'};
    root.ColumnWidth = {'1x'};
    root.Padding = [12 12 12 12];
    root.RowSpacing = 10;

    header = uipanel(root,'Title','Budget');
    header.Layout.Row = 1;

    hg = uigridlayout(header,[1 7]);
    hg.ColumnWidth = {'1x',70,150,170,170,120,120};
    hg.Padding = [10 8 10 8];

    uilabel(hg,'Text','Monthly Budget Planner','FontWeight','bold','FontSize',16);

    uilabel(hg,'Text','Income','FontWeight','bold','HorizontalAlignment','right').Layout.Column = 2;
    income = uieditfield(hg,'numeric','Value',4000,'Limits',[0 Inf]);
    income.Layout.Column = 3;

    spendLbl = uilabel(hg,'Text','Spending: $0.00','FontWeight','bold');
    spendLbl.Layout.Column = 4;

    remainLbl = uilabel(hg,'Text','Remaining: $0.00','FontWeight','bold');
    remainLbl.Layout.Column = 5;

    resetBtn = uibutton(hg,'push','Text','Reset');
    resetBtn.Layout.Column = 6;

    collapseBtn = uibutton(hg,'push','Text','Collapse Details');
    collapseBtn.Layout.Column = 7;

    bodyPanel = uipanel(root,'Title','');
    bodyPanel.Layout.Row = 2;

    % Prefer scrollable body if available
    try
        bodyPanel.Scrollable = 'on';
    catch
    end

    body = uigridlayout(bodyPanel,[1 1]);
    body.Padding = [8 8 8 8];

    % Main grid: n budget rows + 2 detail rows
    main = uigridlayout(body,[n+2, 5]);
    main.RowHeight = [repmat({48},1,n), {270}, {290}];
    main.ColumnWidth = {'1x', 300, 130, 30, 150};
    main.RowSpacing = 10;
    main.ColumnSpacing = 10;
    main.Padding = [6 6 6 6];

    sliders = gobjects(n,1);
    edits   = gobjects(n,1);
    buttons = gobjects(n,1);

    for i = 1:n
        name = items{i,1};
        cat  = items{i,2};
        val  = items{i,3};

        uilabel(main,'Text',sprintf('%s (%s)',name,cat), ...
            'FontWeight','bold','Layout',struct('Row',i,'Column',1));

        maxLim = max(10000, ceil(2*val/10)*10);
        sliders(i) = uislider(main,'Limits',[0 maxLim],'Value',val, ...
            'Layout',struct('Row',i,'Column',2));
        sliders(i).MajorTicks = [];
        sliders(i).MinorTicks = [];

        edits(i) = uieditfield(main,'numeric','Value',val,'Limits',[0 Inf], ...
            'Layout',struct('Row',i,'Column',3));

        uilabel(main,'Text','$','HorizontalAlignment','center', ...
            'Layout',struct('Row',i,'Column',4));

        buttons(i) = uibutton(main,'push','Text','', ...
            'Layout',struct('Row',i,'Column',5));
        buttons(i).Visible = 'off';

        sliders(i).ValueChangingFcn = @(~,evt) onSliderChanging(i, evt.Value);
        sliders(i).ValueChangedFcn  = @(~,~) onSliderChanged(i);
        edits(i).ValueChangedFcn    = @(~,~) onEditChanged(i);

        if i == idxUtilities
            buttons(i).Text = 'Breakdown ▸';
            buttons(i).Visible = 'on';
            buttons(i).ButtonPushedFcn = @toggleUtilities;
        elseif i == idxVehicle
            buttons(i).Text = 'Details ▸';
            buttons(i).Visible = 'on';
            buttons(i).ButtonPushedFcn = @toggleVehicle;
        end
    end

    % ---- Utilities Breakdown (uitable for scroll wheel) ----
    utilPanelRow = n+1;
    utilPanel = uipanel(main,'Title','Utilities Breakdown','Visible','off');
    utilPanel.Layout.Row = utilPanelRow;
    utilPanel.Layout.Column = [1 5];

    ug = uigridlayout(utilPanel,[2 1]);
    ug.RowHeight = {34,'1x'};
    ug.ColumnWidth = {'1x'};
    ug.Padding = [10 10 10 10];
    ug.RowSpacing = 8;

    utilTop = uigridlayout(ug,[1 3]);
    utilTop.Layout.Row = 1;
    utilTop.ColumnWidth = {'1x',180,110};
    utilTop.Padding = [0 0 0 0];

    uilabel(utilTop,'Text','Edit monthly amounts. Check "Included" if included in rent.');
    utilTotalLbl = uilabel(utilTop,'Text','Total: $0.00','FontWeight','bold','HorizontalAlignment','right');
    utilTotalLbl.Layout.Column = 2;
    utilApplyBtn = uibutton(utilTop,'push','Text','Apply ➜');
    utilApplyBtn.Layout.Column = 3;

    utilItems    = {'Electric';'Water';'Gas';'Internet';'Trash/Sewer';'Other'};
    utilMonthly  = [80;40;120;50;25;0];
    utilIncluded = false(size(utilItems));

    utilTable = uitable(ug, ...
        'Data', table(utilItems, utilMonthly, utilIncluded, ...
                      'VariableNames',{'Item','Monthly','Included'}), ...
        'ColumnName', {'Item','Monthly ($)','Included in rent?'}, ...
        'ColumnEditable', [false true true], ...
        'RowName', {}, ...
        'CellEditCallback', @onUtilEdited);
    utilTable.Layout.Row = 2;

    utilApplyBtn.ButtonPushedFcn = @applyUtilitiesToBudget;

    % ---- Vehicle Details ----
    carPanelRow = n+2;
    carPanel = uipanel(main,'Title','Vehicle Payment Details','Visible','off');
    carPanel.Layout.Row = carPanelRow;
    carPanel.Layout.Column = [1 5];

    cg = uigridlayout(carPanel,[6 4]);
    cg.RowHeight = {32,32,32,32,40,'1x'};
    cg.ColumnWidth = {170,'1x',170,'1x'};
    cg.Padding = [10 10 10 10];
    cg.RowSpacing = 8;
    cg.ColumnSpacing = 10;

    uilabel(cg,'Text','Vehicle Price ($)','FontWeight','bold');
    priceField = uieditfield(cg,'numeric','Value',25000,'Limits',[0 Inf]);

    uilabel(cg,'Text','Down Payment ($)','FontWeight','bold','Layout',struct('Row',1,'Column',3));
    downField = uieditfield(cg,'numeric','Value',3000,'Limits',[0 Inf],'Layout',struct('Row',1,'Column',4));

    uilabel(cg,'Text','APR (%)','FontWeight','bold','Layout',struct('Row',2,'Column',1));
    aprField = uieditfield(cg,'numeric','Value',6.5,'Limits',[0 100],'Layout',struct('Row',2,'Column',2));

    uilabel(cg,'Text','Term (months)','FontWeight','bold','Layout',struct('Row',2,'Column',3));
    termField = uieditfield(cg,'numeric','Value',60,'Limits',[1 Inf], ...
        'RoundFractionalValues','on','Layout',struct('Row',2,'Column',4));

    uilabel(cg,'Text','Fees ($)','FontWeight','bold','Layout',struct('Row',3,'Column',1));
    feesField = uieditfield(cg,'numeric','Value',500,'Limits',[0 Inf],'Layout',struct('Row',3,'Column',2));

    calcBtn = uibutton(cg,'push','Text','Calculate','Layout',struct('Row',3,'Column',4));

    payLbl = uilabel(cg,'Text','Estimated Monthly: $0.00','FontWeight','bold','FontSize',14);
    payLbl.Layout.Row = 4; payLbl.Layout.Column = [1 3];

    applyCarBtn = uibutton(cg,'push','Text','Apply ➜','Layout',struct('Row',4,'Column',4));

    calcBtn.ButtonPushedFcn = @calcCarPayment;
    applyCarBtn.ButtonPushedFcn = @applyCarPaymentToBudget;

    % ---- Init + header ----
    resetBtn.ButtonPushedFcn = @resetAll;
    collapseBtn.ButtonPushedFcn = @collapseAll;

    income.ValueChangedFcn = @updateHeaderTotals;

    updateUtilitiesTotal();
    calcCarPayment();
    updateHeaderTotals();

    % ===================== Callbacks =====================
    function onSliderChanging(i, v)
        edits(i).Value = round(v,2);
        updateHeaderTotals();
    end

    function onSliderChanged(i)
        edits(i).Value = round(sliders(i).Value,2);
        updateHeaderTotals();
    end

    function onEditChanged(i)
        sliders(i).Value = edits(i).Value;
        updateHeaderTotals();
    end

    function toggleUtilities(~,~)
        if strcmp(utilPanel.Visible,'off')
            utilPanel.Visible = 'on';
            buttons(idxUtilities).Text = 'Breakdown ▾';
        else
            utilPanel.Visible = 'off';
            buttons(idxUtilities).Text = 'Breakdown ▸';
        end
    end

    function toggleVehicle(~,~)
        if strcmp(carPanel.Visible,'off')
            carPanel.Visible = 'on';
            buttons(idxVehicle).Text = 'Details ▾';
        else
            carPanel.Visible = 'off';
            buttons(idxVehicle).Text = 'Details ▸';
        end
    end

    function onUtilEdited(~,~)
        updateUtilitiesTotal();
    end

    function updateUtilitiesTotal()
        t = utilTable.Data;
        total = 0;
        for r = 1:height(t)
            if ~logical(t.Included(r))
                total = total + double(t.Monthly(r));
            end
        end
        utilTotalLbl.Text = sprintf('Total: $%.2f', total);
    end

    function applyUtilitiesToBudget(~,~)
        t = utilTable.Data;
        total = 0;
        for r = 1:height(t)
            if ~logical(t.Included(r))
                total = total + double(t.Monthly(r));
            end
        end
        edits(idxUtilities).Value = total;
        sliders(idxUtilities).Value = total;
        updateHeaderTotals();
    end

    function calcCarPayment(~,~)
        price = priceField.Value;
        down  = downField.Value;
        apr   = aprField.Value/100;
        term  = max(1, round(termField.Value));
        fees  = feesField.Value;

        principal = max(0, price + fees - down);
        r = apr/12;
        if r <= 0
            pmt = principal/term;
        else
            pmt = principal * (r*(1+r)^term) / ((1+r)^term - 1);
        end
        payLbl.Text = sprintf('Estimated Monthly: $%.2f', pmt);
        payLbl.UserData = pmt;
    end

    function applyCarPaymentToBudget(~,~)
        calcCarPayment();
        pmt = payLbl.UserData;
        edits(idxVehicle).Value = pmt;
        sliders(idxVehicle).Value = pmt;
        updateHeaderTotals();
    end

    function updateHeaderTotals(~,~)
        spend = sum(arrayfun(@(h) double(h.Value), edits));
        spendLbl.Text = sprintf('Spending: $%.2f', spend);
        rem = income.Value - spend;
        remainLbl.Text = sprintf('Remaining: $%.2f', rem);
    end

    function resetAll(~,~)
        for k = 1:n
            edits(k).Value = defaults(k);
            sliders(k).Value = defaults(k);
        end
        % Reset utilities table to defaults
        utilTable.Data.Monthly = utilMonthly;
        utilTable.Data.Included = utilIncluded;

        updateUtilitiesTotal();
        calcCarPayment();
        updateHeaderTotals();
    end

    function collapseAll(~,~)
        utilPanel.Visible = 'off';
        carPanel.Visible  = 'off';
        buttons(idxUtilities).Text = 'Breakdown ▸';
        buttons(idxVehicle).Text   = 'Details ▸';
    end

end