/*
#define定义
斜杠("\")是用来续行的，
"#"用来把参数转换成字符串，是给参数加上双引号。
"##"则用来连接前后两个参数，把它们变成一个字符串。
"#@"是给参数加上单引号。
*/

#define Conn(x,y) x##y

#define ToChar(a) #@a

#define ToString(x) #x



int n = Conn(123, 456); // 结果就是n=123456;

char * str = Conn("asdf", "adf"); // 结果就是 str = "asdfadf";

char a = ToChar(1); // 结果就是a='1';

char* str = ToString(123132); // 就成了str="123132";

int main(){

}

