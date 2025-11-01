//!!METHOD 2:
for(int c = 0; c < length; c++)
{
    if (isValidDir(dance.at(c)))
    {
    }
    else if (isdigit(dance.at(c)))
    {
    }
}

bool proccessDigit(string dance, int &c)
{
    c++;
    if (c == text.size() - 1)
        return false;
    
}

bool proccesDir(string dance, int &c)
{

    c++;
    if (c == text.size())
        return false;
    if (dance[c] == '/')
    {
        return true;
    }
    return false;
}


_________________
string temp = ""
for (int i = 0; i < length; i++){ 
if(dance[i] == '/'){ 
    if(!isValidBeat(temp)){
        return false; 
    }
    temp = "" 
}
    temp += dance[i]
}

bool isValidBeat(string s){ 
    int length = static_cast<int>(s.size); 
    if(s == ""){
        return true;
    }
    if(length > 3){ 
        return false; 
    }
    else if(length == 3){ 
        if(isdigit(s[0]) && isdigit(s[1]) && isValidDir(s[2])){
            ; 
        }else{
            return false; 
        }
    }else if(length == 2){ 
        if(isdigit(s[0]) && isValidDir(s[1])){
            ; 
        }else{
            return false; 
        }
    } else{ 
        if(isValidDir(s[0])){
            ;
        }else{
            return false; 
        }
    }
}