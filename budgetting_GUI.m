function budgetPlannerGUI()
% budgetPlannerGUI - Budget planner UI with sliders + edit fields + take-home estimator
% Auto-scales to different screen sizes using normalized figure + weighted grid rows
%
% Run: budgetPlannerGUI

%% Defaults
salaryAnnualDefault = 100000;
effectiveTaxRateDefault = 0.259;

items = { ...
    'Nelnet Loan',          'Needs',   180; ...
    'FAFSA',                'Needs',   200; ...
    'Rent',                 'Needs',  2400; ...
    'Utilities',            'Needs',   200; ...
    'Internet',             'Needs',    50; ...
    'Phone',                'Needs',    80; ...
    'Auto Insurance',       'Needs',   200; ...
    'Dining Out / Coffee',  'Wants',   300; ...
    'Vehicle Payment',      'Wants',   450; ...
    'Gas / Transportation', 'Wants',   150; ...
    'Subscriptions',        'Wants',    60; ...
    'Retirement',           'Savings', 720; ...
    'Emergency Fund',       'Savings', 300; ...
    'Short Term',           'Savings', 180  ...
    };

n = size(items,1);
defaultMonthly = cell2mat(items(:,3));

% Slider bounds (large max values)
minVals = zeros(n,1);
maxVals = zeros(n,1);
for i = 1:n
    v = items{i,3};
    minVals(i) = 0;
    maxVals(i) = max(10000, ceil(8*v/10)*10);
end

WHITE = [1 1 1];

%% Build UI (UPDATED: normalized so it scales with screen)
fig = uifigure( ...
    'Name','Budget Planner (Sliders)', ...
    'Units','normalized', ...
    'Position',[0.08 0.08 0.84 0.84]);

gl = uigridlayout(fig,[1 2]);
gl.ColumnWidth = {640, '1x'};   % left is a bit wider; right fills
gl.RowHeight = {'1x'};
gl.Padding = [10 10 10 10];
gl.ColumnSpacing = 10;

%% LEFT SIDE (3 PANELS): Quick Actions, Pay, Budget
left = uigridlayout(gl,[3 1]);
left.Layout.Row = 1; left.Layout.Column = 1;

% UPDATED: weighted heights so it scales on smaller screens
left.RowHeight = {'0.15x', '0.25x', '1x'};
left.ColumnWidth = {'1x'};
left.RowSpacing = 10;
left.Padding = [0 0 0 0];

% Panel 1: Quick Actions
btnPanel = uipanel(left,'Title','Quick Actions');
btnPanel.Layout.Row = 1; btnPanel.Layout.Column = 1;

bg = uigridlayout(btnPanel,[1 3]);
bg.ColumnWidth = {'1x','1x','1x'};
bg.RowHeight = {'1x'};
bg.Padding = [10 10 10 10];
bg.ColumnSpacing = 12;

resetBtn  = uibutton(bg,'Text','Reset','FontSize',12,'ButtonPushedFcn',@resetDefaults);
allocBtn  = uibutton(bg,'Text','Allocate','FontSize',12,'ButtonPushedFcn',@allocateRemaining);
exportBtn = uibutton(bg,'Text','Export CSV','FontSize',12,'ButtonPushedFcn',@exportCSV);

% Panel 2: Pay / Take-Home
salaryPanel = uipanel(left,'Title','Pay / Take-Home');
salaryPanel.Layout.Row = 2; salaryPanel.Layout.Column = 1;

sgLeft = uigridlayout(salaryPanel,[5 4]);
sgLeft.RowHeight = {'1x','1x','1x','1x','1x'};
sgLeft.ColumnWidth = {240,'1x',60,120};
sgLeft.Padding = [10 10 10 10];
sgLeft.RowSpacing = 10;
sgLeft.ColumnSpacing = 10;

uilabel(sgLeft,'Text','Salary (Annual):','FontWeight','bold');
salaryField = uieditfield(sgLeft,'numeric', ...
    'Value',salaryAnnualDefault,'Limits',[0 Inf],'ValueDisplayFormat','%.0f');
uilabel(sgLeft,'Text','$');
uilabel(sgLeft,'Text','');

uilabel(sgLeft,'Text','Effective Tax Rate:','FontWeight','bold');
taxRateField = uieditfield(sgLeft,'numeric', ...
    'Value',effectiveTaxRateDefault,'Limits',[0 0.60],'ValueDisplayFormat','%.3f');
uilabel(sgLeft,'Text','');
uilabel(sgLeft,'Text','(0–0.60)','HorizontalAlignment','left');

uilabel(sgLeft,'Text','Net Take Home (Annual):','FontWeight','bold');
takeHomeField = uieditfield(sgLeft,'numeric', ...
    'Value',estimateTakeHome(salaryAnnualDefault,effectiveTaxRateDefault), ...
    'Limits',[0 Inf],'ValueDisplayFormat','%.0f');
uilabel(sgLeft,'Text','$');
uilabel(sgLeft,'Text','');

uilabel(sgLeft,'Text','Auto-calc take-home:','FontWeight','bold');
autoTakeHome = uicheckbox(sgLeft,'Value',true,'Text','On');
uilabel(sgLeft,'Text','');
uilabel(sgLeft,'Text','');

uilabel(sgLeft,'Text','Net Take Home (Monthly):','FontWeight','bold');
takeHomeMonthlyLabel = uilabel(sgLeft,'Text','$0.00','FontWeight','bold');
uilabel(sgLeft,'Text','');
uilabel(sgLeft,'Text','');

% Pay callbacks
salaryField.ValueChangedFcn = @updateTakeHomeFromSalary;
taxRateField.ValueChangedFcn = @updateTakeHomeFromSalary;
autoTakeHome.ValueChangedFcn = @updateTakeHomeFromSalary;
takeHomeField.ValueChangedFcn = @updateAll;

% Panel 3: Budget sliders (scrollable)
budgetPanel = uipanel(left,'Title','Budget','Scrollable','on');
budgetPanel.Layout.Row = 3; budgetPanel.Layout.Column = 1;

lg = uigridlayout(budgetPanel,[n 4]);
lg.RowHeight = repmat({'1x'},1,n);           % UPDATED: scalable rows
lg.ColumnWidth = {260, '1x', 120, 40};
lg.Padding = [10 10 10 10];
lg.RowSpacing = 10;
lg.ColumnSpacing = 10;

sliders = gobjects(n,1);
editFields = gobjects(n,1);

for i = 1:n
    name = items{i,1};
    cat  = items{i,2};
    val  = items{i,3};

    uilabel(lg,'Text',sprintf('%s (%s)',name,cat), ...
        'HorizontalAlignment','left','FontWeight','bold');

    s = uislider(lg, ...
        'Limits',[minVals(i) maxVals(i)], ...
        'Value',val, ...
        'MajorTicks',[], ...
        'MinorTicks',[], ...
        'ValueChangingFcn',@(src,evt) onSliderChanging(i,evt.Value), ...
        'ValueChangedFcn',@(src,evt) onSliderChanged(i,evt.Value));

    ef = uieditfield(lg,'numeric', ...
        'Value',val, ...
        'Limits',[minVals(i) maxVals(i)], ...
        'ValueDisplayFormat','%.0f', ...
        'ValueChangedFcn',@(src,evt) onEditChanged(i,src.Value));

    uilabel(lg,'Text','$','HorizontalAlignment','left');

    sliders(i) = s;
    editFields(i) = ef;
end

%% RIGHT SIDE: Status + Paycheck + Table + Bottom totals
right = uipanel(gl,'Title','Budget Overview');
right.Layout.Row = 1; right.Layout.Column = 2;

rg = uigridlayout(right,[4 1]);

% UPDATED: weighted heights so it scales on smaller screens
rg.RowHeight = {'0.10x', '0.35x', '1x', '0.45x'};
rg.ColumnWidth = {'1x'};
rg.Padding = [10 10 10 10];
rg.RowSpacing = 10;

% Status
warnPanel = uipanel(rg,'Title','Status');
wg = uigridlayout(warnPanel,[1 1]);
wg.Padding = [10 8 10 8];
statusLbl = uilabel(wg,'Text','OK','FontWeight','bold');

% Paycheck Breakdown
payPanel = uipanel(rg,'Title','Paycheck Breakdown (Bi-Weekly)');
payGrid = uigridlayout(payPanel,[8 4]);
payGrid.RowHeight = repmat({'1x'},1,8);      % UPDATED: scalable rows
payGrid.ColumnWidth = {220, 120, 150, '1x'};
payGrid.Padding = [10 10 10 10];
payGrid.RowSpacing = 6;
payGrid.ColumnSpacing = 10;

uilabel(payGrid,'Text','Tax Type','FontWeight','bold');
uilabel(payGrid,'Text','Rate','FontWeight','bold');
uilabel(payGrid,'Text','Bi-Weekly ($)','FontWeight','bold');
uilabel(payGrid,'Text','Notes','FontWeight','bold');

uilabel(payGrid,'Text','Federal (est.)');
federalRate = uilabel(payGrid,'Text','—');
federalAmt  = uilabel(payGrid,'Text','$0.00','FontWeight','bold');
uilabel(payGrid,'Text','Effective-based estimate','FontAngle','italic');

uilabel(payGrid,'Text','FICA');
ficaRate = uilabel(payGrid,'Text','7.65%');
ficaAmt  = uilabel(payGrid,'Text','$0.00','FontWeight','bold');
uilabel(payGrid,'Text','Social Security + Medicare','FontAngle','italic');

uilabel(payGrid,'Text','State (MA est.)');
stateRate = uilabel(payGrid,'Text','5.00%');
stateAmt  = uilabel(payGrid,'Text','$0.00','FontWeight','bold');
uilabel(payGrid,'Text','MA flat income tax (rough)','FontAngle','italic');

uilabel(payGrid,'Text',''); uilabel(payGrid,'Text',''); uilabel(payGrid,'Text',''); uilabel(payGrid,'Text','');

uilabel(payGrid,'Text','Total Taxes','FontWeight','bold');
totalTaxRate = uilabel(payGrid,'Text','—','FontWeight','bold');
totalTaxAmt  = uilabel(payGrid,'Text','$0.00','FontWeight','bold');
uilabel(payGrid,'Text','(bi-weekly)','FontAngle','italic');

uilabel(payGrid,'Text','Income After Taxes','FontWeight','bold');
afterTaxRate = uilabel(payGrid,'Text','—');
afterTaxAmt  = uilabel(payGrid,'Text','$0.00','FontWeight','bold');
uilabel(payGrid,'Text','(bi-weekly)','FontAngle','italic');

uilabel(payGrid,'Text','Take-Home Pay','FontWeight','bold');
takeHomeRate2 = uilabel(payGrid,'Text','—');
takeHomeAmt2  = uilabel(payGrid,'Text','$0.00','FontWeight','bold');
uilabel(payGrid,'Text','What hits your bank','FontAngle','italic');

% Table
t = uitable(rg);
t.ColumnName = {'Category','Expense','Monthly ($)','Yearly ($)'};
t.ColumnEditable = [false false false false];
t.ColumnFormat = {'char','char','numeric','numeric'};

% Bottom totals panels
bottom = uigridlayout(rg,[1 2]);
bottom.ColumnWidth = {'1x','1x'};
bottom.RowHeight = {'1x'};
bottom.Padding = [0 0 0 0];
bottom.ColumnSpacing = 12;

% Totals
sumPanel = uipanel(bottom,'Title','Totals & Remaining');
tg = uigridlayout(sumPanel,[6 4]);
tg.RowHeight = repmat({'1x'},1,6);           % UPDATED: scalable rows
tg.ColumnWidth = {260, 220, 260, 220};
tg.Padding = [10 10 10 10];
tg.RowSpacing = 10;
tg.ColumnSpacing = 14;

mkLbl = @(txt) uilabel(tg,'Text',txt,'FontWeight','bold','HorizontalAlignment','left');
mkVal = @(txt) uilabel(tg,'Text',txt,'FontWeight','bold','HorizontalAlignment','left');

mkLbl('Total Expenses (Monthly):'); totalMonthlyLbl = mkVal('$0.00');
mkLbl('Total Expenses (Yearly):');  totalYearlyLbl  = mkVal('$0.00');

mkLbl('Remaining (Monthly):');      remainMonthlyLbl = mkVal('$0.00');
mkLbl('Remaining (Yearly):');       remainYearlyLbl  = mkVal('$0.00');

mkLbl('Remaining % of Take-Home:'); remainPctLbl = mkVal('0.0%');
uilabel(tg,'Text','(after expenses)','FontAngle','italic','HorizontalAlignment','left');
uilabel(tg,'Text','');

mkLbl('Guideline check:'); guidelineLbl = mkVal('—');
uilabel(tg,'Text','(Needs/Wants/Savings)','FontAngle','italic','HorizontalAlignment','left');
uilabel(tg,'Text','');

% Category totals
catPanel = uipanel(bottom,'Title','Category Totals');
cg = uigridlayout(catPanel,[6 3]);
cg.RowHeight = repmat({'1x'},1,6);           % UPDATED: scalable rows
cg.ColumnWidth = {160, 220, 220};
cg.Padding = [10 10 10 10];
cg.RowSpacing = 10;
cg.ColumnSpacing = 14;

uilabel(cg,'Text','Category','FontWeight','bold','HorizontalAlignment','left');
uilabel(cg,'Text','Monthly ($)','FontWeight','bold','HorizontalAlignment','left');
uilabel(cg,'Text','% of Net','FontWeight','bold','HorizontalAlignment','left');

uilabel(cg,'Text','Needs','FontWeight','bold');
needsMonthlyVal = uilabel(cg,'Text','$0.00','FontWeight','bold');
needsMonthlyPct = uilabel(cg,'Text','0.0%','FontWeight','bold');

uilabel(cg,'Text','Wants','FontWeight','bold');
wantsMonthlyVal = uilabel(cg,'Text','$0.00','FontWeight','bold');
wantsMonthlyPct = uilabel(cg,'Text','0.0%','FontWeight','bold');

uilabel(cg,'Text','Savings','FontWeight','bold');
savingsMonthlyVal = uilabel(cg,'Text','$0.00','FontWeight','bold');
savingsMonthlyPct = uilabel(cg,'Text','0.0%','FontWeight','bold');

uilabel(cg,'Text','Total','FontWeight','bold');
totalCatMonthlyVal = uilabel(cg,'Text','$0.00','FontWeight','bold');
totalCatMonthlyPct = uilabel(cg,'Text','100.0%','FontWeight','bold');

uilabel(cg,'Text','Tip','FontWeight','bold');
uilabel(cg,'Text','Try 60/20/20 or 50/30/20','FontAngle','italic');
uilabel(cg,'Text','Adjust as needed','FontAngle','italic');

%% Initial render
updateTakeHomeFromSalary();
updateAll();

%% ---- Callbacks ----
    function updateTakeHomeFromSalary(~,~)
        if autoTakeHome.Value
            takeHomeField.Value = estimateTakeHome(salaryField.Value, taxRateField.Value);
            takeHomeField.Editable = 'off';
        else
            takeHomeField.Editable = 'on';
        end
        updateAll();
    end

    function onSliderChanging(i, newVal)
        editFields(i).Value = round(newVal);
        quickUpdateTotals();
    end

    function onSliderChanged(i, newVal)
        editFields(i).Value = round(newVal);
        updateAll();
    end

    function onEditChanged(i, newVal)
        v = round(newVal);
        lim = sliders(i).Limits;
        v = min(max(v, lim(1)), lim(2));
        editFields(i).Value = v;
        sliders(i).Value = v;
        updateAll();
    end

    function resetDefaults(~,~)
        for k = 1:n
            sliders(k).Value = defaultMonthly(k);
            editFields(k).Value = defaultMonthly(k);
        end
        updateAll();
    end

    function allocateRemaining(~,~)
        choice = uiconfirm(fig, ...
            "Where should your remaining monthly money go?", ...
            "Allocate Remaining", ...
            "Options", ["Retirement","Emergency Fund","Short Term","Cancel"], ...
            "DefaultOption", "Emergency Fund", ...
            "CancelOption", "Cancel");
        if choice == "Cancel"; return; end

        takeHomeMonthly = takeHomeField.Value/12;
        monthlyVals = round(arrayfun(@(s) s.Value, sliders));
        remainingMonthly = takeHomeMonthly - sum(monthlyVals);

        if remainingMonthly <= 0
            uialert(fig,"No remaining money to allocate (you may be at or over budget).","Nothing to Allocate");
            return;
        end

        idx = find(strcmp(items(:,1), char(choice)), 1);
        if isempty(idx)
            uialert(fig,"Couldn't find the target category in the items list.","Error");
            return;
        end

        newVal = sliders(idx).Value + remainingMonthly;
        lim = sliders(idx).Limits;
        newVal = min(max(newVal, lim(1)), lim(2));
        sliders(idx).Value = newVal;
        editFields(idx).Value = round(newVal);
        updateAll();
    end

    function exportCSV(~,~)
        [file,path] = uiputfile('budget_export.csv','Save Budget CSV');
        if isequal(file,0); return; end
        monthlyVals = round(arrayfun(@(s) s.Value, sliders));
        yearlyVals = monthlyVals * 12;
        T = table(string(items(:,2)), string(items(:,1)), monthlyVals, yearlyVals, ...
            'VariableNames', {'Category','Expense','Monthly','Yearly'});
        writetable(T, fullfile(path,file));
        uialert(fig,"Exported successfully!","CSV Saved");
    end

    function updateAll(~,~)
        takeHomeAnnual = takeHomeField.Value;
        takeHomeMonthly = takeHomeAnnual/12;
        takeHomeMonthlyLabel.Text = money(takeHomeMonthly);

        % ---- Paycheck Breakdown (Bi-weekly) ----
        payPeriods = 26;
        grossBiWeekly = salaryField.Value / payPeriods;

        effectiveTotalRate = taxRateField.Value;
        ficaRateVal  = 0.0765;
        stateRateVal = 0.0500;

        totalTaxBiWeekly = grossBiWeekly * effectiveTotalRate;
        ficaBiWeekly  = grossBiWeekly * ficaRateVal;
        stateBiWeekly = grossBiWeekly * stateRateVal;

        federalBiWeekly = max(0, totalTaxBiWeekly - ficaBiWeekly - stateBiWeekly);
        afterTaxBiWeekly = grossBiWeekly - totalTaxBiWeekly;

        federalRate.Text = sprintf('%.2f%%', max(0,(federalBiWeekly / grossBiWeekly)*100));
        federalAmt.Text  = money(federalBiWeekly);

        ficaRate.Text = sprintf('%.2f%%', ficaRateVal*100);
        ficaAmt.Text  = money(ficaBiWeekly);

        stateRate.Text = sprintf('%.2f%%', stateRateVal*100);
        stateAmt.Text  = money(stateBiWeekly);

        totalTaxRate.Text = sprintf('%.2f%%', effectiveTotalRate*100);
        totalTaxAmt.Text  = money(totalTaxBiWeekly);

        afterTaxRate.Text = sprintf('%.2f%%', (afterTaxBiWeekly / grossBiWeekly)*100);
        afterTaxAmt.Text  = money(afterTaxBiWeekly);

        takeHomeRate2.Text = sprintf('%.2f%%', (afterTaxBiWeekly / grossBiWeekly)*100);
        takeHomeAmt2.Text  = money(afterTaxBiWeekly);

        % ---- Table + totals ----
        data = cell(n,4);
        monthlyVals = zeros(n,1);
        cats = cell(n,1);

        for k = 1:n
            monthlyVals(k) = round(sliders(k).Value);
            data{k,1} = items{k,2};
            data{k,2} = items{k,1};
            data{k,3} = monthlyVals(k);
            data{k,4} = monthlyVals(k)*12;
            cats{k} = items{k,2};
        end
        t.Data = data;

        totalMonthly = sum(monthlyVals);
        totalYearly  = totalMonthly*12;

        remainingMonthly = takeHomeMonthly - totalMonthly;
        remainingYearly  = takeHomeAnnual - totalYearly;

        totalMonthlyLbl.Text = money(totalMonthly);
        totalYearlyLbl.Text  = money(totalYearly);
        remainMonthlyLbl.Text = money(remainingMonthly);
        remainYearlyLbl.Text  = money(remainingYearly);

        if takeHomeAnnual > 0
            remainPctLbl.Text = sprintf('%.1f%%', (remainingYearly / takeHomeAnnual)*100);
        else
            remainPctLbl.Text = '—';
        end

        needsMonthly   = sum(monthlyVals(strcmp(cats,'Needs')));
        wantsMonthly   = sum(monthlyVals(strcmp(cats,'Wants')));
        savingsMonthly = sum(monthlyVals(strcmp(cats,'Savings')));

        needsPct   = safePct(needsMonthly, takeHomeMonthly);
        wantsPct   = safePct(wantsMonthly, takeHomeMonthly);
        savingsPct = safePct(savingsMonthly, takeHomeMonthly);

        needsMonthlyVal.Text = money(needsMonthly);
        wantsMonthlyVal.Text = money(wantsMonthly);
        savingsMonthlyVal.Text = money(savingsMonthly);

        needsMonthlyPct.Text = sprintf('%.1f%%', needsPct);
        wantsMonthlyPct.Text = sprintf('%.1f%%', wantsPct);
        savingsMonthlyPct.Text = sprintf('%.1f%%', savingsPct);

        totalCatMonthlyVal.Text = money(needsMonthly + wantsMonthly + savingsMonthly);
        totalCatMonthlyPct.Text = '100.0%';

        guidelineLbl.Text = guidelineText(needsPct, wantsPct, savingsPct);

        if remainingMonthly < 0
            statusLbl.Text = '⚠ Over budget — reduce expenses or increase take-home';
        else
            statusLbl.Text = 'OK — within budget';
        end

        forceWhite(totalMonthlyLbl, totalYearlyLbl, remainMonthlyLbl, remainYearlyLbl, remainPctLbl, ...
                   guidelineLbl, statusLbl, ...
                   needsMonthlyVal, wantsMonthlyVal, savingsMonthlyVal, ...
                   needsMonthlyPct, wantsMonthlyPct, savingsMonthlyPct, ...
                   totalCatMonthlyVal, totalCatMonthlyPct, ...
                   federalRate, federalAmt, ficaRate, ficaAmt, stateRate, stateAmt, ...
                   totalTaxRate, totalTaxAmt, afterTaxRate, afterTaxAmt, takeHomeRate2, takeHomeAmt2);
    end

    function quickUpdateTotals()
        takeHomeMonthly = takeHomeField.Value/12;
        monthlyVals = round(arrayfun(@(s) s.Value, sliders));
        totalMonthly = sum(monthlyVals);
        remainingMonthly = takeHomeMonthly - totalMonthly;

        if remainingMonthly < 0
            statusLbl.Text = '⚠ Over budget — reduce expenses or increase take-home';
        else
            statusLbl.Text = 'OK — within budget';
        end
        forceWhite(statusLbl);
    end
end

%% ---- Helpers ----
function annualNet = estimateTakeHome(salaryAnnual, effectiveTaxRate)
annualNet = salaryAnnual * (1 - effectiveTaxRate);
end

function p = safePct(partMonthly, totalMonthly)
if totalMonthly <= 0
    p = 0;
else
    p = (partMonthly / totalMonthly) * 100;
end
end

function s = guidelineText(needsPct, wantsPct, savingsPct)
ok = (needsPct >= 45 && needsPct <= 65) && (wantsPct <= 35) && (savingsPct >= 10);
if ok
    s = sprintf('Looks reasonable (Needs %.0f%% / Wants %.0f%% / Savings %.0f%%)', needsPct, wantsPct, savingsPct);
else
    s = sprintf('Review mix (Needs %.0f%% / Wants %.0f%% / Savings %.0f%%)', needsPct, wantsPct, savingsPct);
end
end

function forceWhite(varargin)
for i = 1:nargin
    %varargin{i}.FontColor = [1 1 1];
end
end

function s = money(x)
if x < 0
    s = sprintf('-$%s', addCommas(sprintf('%.2f', abs(x))));
else
    s = sprintf('$%s', addCommas(sprintf('%.2f', x)));
end
end

function out = addCommas(numStr)
parts = split(numStr,'.');
intPart = char(parts(1));
decPart = '';
if numel(parts) > 1
    decPart = ['.' char(parts(2))];
end
neg = false;
if startsWith(intPart,'-')
    neg = true;
    intPart = intPart(2:end);
end
intPart = fliplr(intPart);
chunks = regexp(intPart,'.{1,3}','match');
intPart = strjoin(chunks,',');
intPart = fliplr(intPart);
if neg
    intPart = ['-' intPart];
end
out = [intPart decPart];
end
