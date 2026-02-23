**Beer #** : 
Ale or Lager? : 
Style : 
Color (scale 0-8) : 
Aroma Strength (scale 0-5) : 
Aroma reminds me of... 
Taste Strength (scale 0-5) : 
Taste Reminds me of... 
Mouthfeel (scale 0-5) : 
Finish Strength (scale 0-5) : 
Finish reminds me of.... 
Did I like it? 
Would I buy this beer? 
Other Comments...

---

**Beer 1** : 
Ale or Lager? : 
Style : 
Color (scale 0-8) : 
```meta-bind
INPUT[inlineSelect(
	option(0, "0 - Water"),
	option(1, "1 - Light Straw"),
	option(2, "2 - Pale Straw"),
	option(3, "3 - Dark Straw"),
	option(4, "4 - Light Amber"),
	option(5, "5 - Pale Amber"),
	option(6, "6 - Dark Amber"),
	option(7, "7 - Very Dark Amber"),
	option(8, "8 - Black")
):color]
```
Aroma Strength (scale 0-5) : 
```meta-bind
INPUT[inlineSelect(
	option(0, "0 - None"),
	option(1, "1 - Very Low"),
	option(2, "2 - Low"),
	option(3, "3 - Medium"),
	option(4, "4 - High"),
	option(5, "5 - Very High")
):aroma_strength]
```
Aroma reminds me of... 

Taste Strength (scale 0-5) : 
```meta-bind
INPUT[inlineSelect(
	option(0, "0 - None"),
	option(1, "1 - Very Low"),
	option(2, "2 - Low"),
	option(3, "3 - Medium"),
	option(4, "4 - High"),
	option(5, "5 - Very High")
):taste_strength]
```
Taste Reminds me of... 

Mouthfeel (scale 0-5) : 
```meta-bind
INPUT[inlineSelect(
	option(0, "0 - Water"),
	option(1, "1 - Very Thin"),
	option(2, "2 - Thin"),
	option(3, "3 - Medium"),
	option(4, "4 - Creamy"),
	option(5, "5 - Whole Milk")
):mouthfeel]
```
Finish Strength (scale 0-5) : 
```meta-bind
INPUT[inlineSelect(
	option(0, "0 - None"),
	option(1, "1 - Very Short"),
	option(2, "2 - Short"),
	option(3, "3 - Medium"),
	option(4, "4 - Long"),
	option(5, "5 - Very Long")
):finish_strength]
```
Finish reminds me of.... 

Did I like it? 
```meta-bind
INPUT[inlineSelect(
	option(0, "No"),
	option(1, "Yes")
):like]
```
Would I buy this beer? 
```meta-bind
INPUT[inlineSelect(
	option(0, "No"),
	option(1, "Yes")
):buy]
```
Other Comments...
