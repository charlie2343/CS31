 # If statement notes: #

### Faulty if statement example:  ###

```
if (payrate > = 18)
    double taxRate = 0.05;
else
    double taxRate = 0.05; //NOT QUITE RIGHT!!! (the variabel is local to the iff statement)

```

How to Properly do it

```
double taxRate

if (payrate > = 18)
    taxRate = 0.05;
else
    taxRate = 0.05; 
```

magic number = number that is hardcoded and wouldn't make sense to external reader. 

### Const keyword ###
const indicates variables wont change. 

#### Conditions ####
always spell out both conditions so they make sense when read alone. 
Example: 
```
if(1 <= rating <= 10) !!Doesnt work because two conditions in one
```
#### How execution of conditions in if statement work ####

```

if(b != 0 && d != 0 && a/b + c/d < 10)
... //If b or d = 0 will p3 of condition be evaluated


```
Answer: No 
if b != 0 is False then the rest doesnst evaluate

##### Notes ######
Think about redundancy with if statements. Are there ones checked implicitly by the if before it
