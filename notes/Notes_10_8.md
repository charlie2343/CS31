type character holds a single character

M2 Switch statements: 
Switch statements are like train track switches. Only switches to case 1 time, then done with checking. 

```
int choice
cin >> choice: 
switch (choice)
{ 
    case 1: 
        cout << "Do thing A" << endl; 
        break; //must manually add exit after condition is checked to exit switch block
    case 2:  //Case 2 and Case 4 will do the same thing as case 4. 
    case 4: 
         cout << "Do thing B" << endl; 
}
```

Most common mistake is forgetting break after switch statement. If there is no break, then it goes past any additional checks and executes everything inside until there is a break. 

#### Switch Statement Limitations ####
Can only read in things of type integer. 

Wrong Examples
```
switch(d)
{ 
case 2.04: //can not contain double (comparing doubles doesn't quite work unless double is power of 2 such as 0.125. Computer can not store exact value of double so it uses approximate values.)
case "Santa Monica" //not int
}
```

#### Arithmetic shorcuts ####
n += 
n *=
n++
n /=

#### While Loops #### 
```
int n = 1; 
while(n <= nTimes){ 

n++
}

//OR

while n = 0
while (n < nTimes){ 

n++
//here n represents the amount of times while loop has executed. ie n = 0 loop when 0 times, n= 1, n = 2 n =3 then stop
}
```

#### While Loop Use Cases ####
while: 
    pros:
      boolean condition
      better for multiple boolean conditions: 
      ie: 
      while(game != "Over" and touchdown < 10 and ...)
    cons: 
      less clear for iteration

#### Loop Exiters ####
Continue moves to next iteration (Dr. Who)
Break exits loop entirely (Loki)



