### 1.1.7 const
1.
Q：const与define区别？
A：
“const常量具有类型，编译器可以进行安全检查；#define宏定义没有数据类型，只是简单的字符串替换，不能进行安全检查”
这个说法是错的，#define定义的宏变量同样存在类型，与字面值常量的类型相同。
正确答案：编译器不会将宏定义加入到符号列表中。
```c++
#define TEST 0  //int型
#define TEST2 128UL   //unsigned long型
#define TEST3 "hello"  //字符串型
#define TEST4 'Q'    //字符型
#define TEST5 3.13159f   //float型
```
---
2.
Q：全局作用域声明的const变量可以被其他文件访问吗？
A:
```c++
const int aa=1;  //不可以被其他文件访问
extern const int bb=2;    //可以被其他文件访问
```
普通变量（非const）默认为extern。要使const变量能够在其他的文件中访问，必须显式地指定它为extern。
----
3.其他重要点
- const对象必须要初始化，且不能修改
- 非const引用只能绑定到与该引用同类型对象。const引用则可以绑定到不同但相关的类型的对象或绑定到右值。 **原因**：因为const只读，不会修改引用原对象
- 由于上面的原因，应该将不修改相应实参的形参定义为const引用。如果将这样的形参定义为非const引用，则毫无必要的限制了该函数的使用。
- 
```c++
int const *x;   //指向const int值的指针x
const int *x;    //同上
int *const x = &initializedVar;    //指向int值的const指针，必须初始化
const int *const x = &initializedVar; //指向const int 值的const指针，必须初始化
```
- 如果使用引用形参的唯一目的是避免复制实参，则应将形参定义为const引用
- 函数的非引用形参，对于调用时的参数是否为const无影响
- const成员函数不能修改调用该函数的对象，const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数。构造函数不能声明为const函数


-----
### 1.1.8 static
1.在data区存放已经初始化的全局静态变量，在bss区存放尚未初始化的全局静态变量，全部变量在main()外不需要写static。
2.类中静态变量和外面的静态变量一样，由于声明为static的变量只被初始化一次，因为它们在单独的静态存储中分配了空间，因此类中的静态变量由对象共享。对于不同的对象，不能有相同静态变量的多个副本。也是因为这个原因，静态变量不能使用构造函数初始化。类中静态变量成员必须定义，因为声明的时候没有分配内存，定义可以给它分配内存，同时赋予了个初值；类中静态函数也同样不依赖于类对象，最好的调用方式为className::staticFucName();
```
class GamePlayer{
private:
	static const int NUM_Turns=5;   //声明的时候同时定义，因为静态常量变量只有一份拷贝，所以需要定义给它分配个内存
	int scores[NUM_TURNS];  //use of constant
	static print_hello(){cout<<"hello"<<endl;}
}
GamePlayer::print_hello();
}
```
3.用static修饰的成员变量在对象中是不占内存的，因为他是不是跟对象一起在堆或栈中生成。

### 1.1.9 sizeof
1.必须知道的
- 空类的大小为1字节
- 一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间
- 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针，vptr的大小
- 虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr，几个基类，几个vptr的长度
- 虚继承，继承基类的vptr


----

### 1.1.10 goto
避免使用goto控制流
在一些函数中，我们可能需要在return 语句之前做一些清理工作，比如释放在函数开始处有malloc申请的内存空间，使用goto总是一种简单的方法：
```c++
int f(){
	int *p = (int *)malloc(sizeof(int));
	*p = 10;
	cout<<*p<<endl;
#ifndef DEBUG
	int error=1;
#endif
	if(error)
		goto END;//do something when go wrong
END:
	cout<<"need free the *p"<<endl;
	free(p);
	return 0;
}
```
但由于goto不符合软件工程的结构化，而且可能使得代码难懂，所以不提倡使用，这个时候我们可以使用do{...}while(0)来做同样的事情
```c++
int ff(){
	int *p = (int*)malloc(sizeof(int));
	*p = 10;
	cout<<*p<<endl;
	do{
#ifndef DEBUG
	int error=1;
#endif
	//do something
	if(error)
		break;  //if error, out
	}while(0);
	cout<<"free"<<endl;
	free(p);
	return 0;
}
```


### 1.1.11 extern
1.C++与C编译区别
在C++中常在头文件见到extern "C"修饰函数，那有什么作用呢？ 是用于C++链接在C语言模块中定义的函数。
C++虽然兼容C，但C++文件中函数编译后生成的符号与C语言生成的不同。因为C++支持函数重载，C++函数编译后生成的符号带有函数参数类型的信息，而C则没有。
例如int add(int a, int b)函数经过C++编译器生成.o文件后，add会变成形如add_int_int之类的, 而C的话则会是形如_add, 就是说：相同的函数，在C和C++中，编译后生成的符号不同。
这就导致一个问题：如果C++中使用C语言实现的函数，在编译链接的时候，会出错，提示找不到对应的符号。此时extern "C"就起作用了：告诉链接器去寻找_add这类的C语言符号，而不是经过C++修饰的符号。

### 1.1.12inline(内联函数)
1.需要知道的
- 类中内联，类中定义的函数是隐式内联函数，如果只声明不定义则需要在定义处加inline成为内联函数
- 内联优势：提高函数执行效率，调用函数的工作：调用前要先保存寄存器，并在返回时恢复；复制实参；程序还必须指向一个新位置执行。
- 内联劣势：如果函数体内的代码较长，内联会导致内存消耗代价比较高。
- 内联函数应该在头文件中定义。把内联函数的定义放在头文件中，可以确保在调用函数时所使用的定义是相同的。


2.虚函数可以是内联函数吗？
A:
- 虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联。
- 内联是在编译器建议编译器内联，而虚函数的多态性在运行期，编译器无法知道运行期调用哪个代码，因此虚函数表现为多态性时（运行期）不可以内联。
- inline virtual 唯一可以内联的时候是：编译器知道所调用的对象是哪个类（如 Base::who()），这只有在编译器具有实际对象而不是对象的指针或引用时才会发生。

---
### 1.1.13 union
联合（union）是一种节省空间的特殊的类，一个 union 可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值。当某个成员被赋值后其他成员变为未定义状态。

### 1.3.4 虚函数
1.类的首地址是虚函数表地址，成员变量根据其继承和声明顺序依次放在后面，在单一继承中，被overwrite的虚函数在虚函数表中得到了更新
```c++
class Parent {
public:
    int iparent;
    Parent ():iparent (10) {}
    virtual void f() { cout << " Parent::f()" << endl; }
    virtual void g() { cout << " Parent::g()" << endl; }
    virtual void h() { cout << " Parent::h()" << endl; }

};

class Child : public Parent {
public:
    int ichild;
    Child():ichild(100) {}
    virtual void f() { cout << "Child::f()" << endl; }
    virtual void g_child() { cout << "Child::g_child()" << endl; }
    virtual void h_child() { cout << "Child::h_child()" << endl; }
};

class GrandChild : public Child{
public:
    int igrandchild;
    GrandChild():igrandchild(1000) {}
    virtual void f() { cout << "GrandChild::f()" << endl; }
    virtual void g_child() { cout << "GrandChild::g_child()" << endl; }
    virtual void h_grandchild() { cout << "GrandChild::h_grandchild()" << endl; }
};
```
```bash
 +-------+                            +-----------------------------------------------------+
0|       +----------------------->   0|GrandChild::f()                                      |
 | vfptr |                            +-----------------------------------------------------+
 +-------+                           1|Parent::g()                                          |
1|  10   |Parent.iparent              +-----------------------------------------------------+
 +-------+                           2|Parent::h()                                          |
2| 100   |Child.ichild                +-----------------------------------------------------+
 +-------+                           3|GrandChild::g_child()                                |
3|       |                            +-----------------------------------------------------+
 | 1000  |GrandChild.igrandchild     4|Child::h_child()                                     |
 +-------+                            +-----------------------------------------------------+
                                     5|GrandChild::h_grandchild()                           |
                                      +-----------------------------------------------------+
```
2.多重继承（多个父类）：每个父类都有自己的续表，子类的成员函数被放到了第一个父类的表中，内存布局中，其父类布局一次按声明顺序排列。
3.https://www.cnblogs.com/qg-whz/p/4909359.html#_label6_0
4.虚函数是动态绑定的，而缺省参数是静态绑定的
```c++
#include <iostream> 
using namespace std; 

class Base 
{ 
    public: 
        virtual void fun ( int x = 10 ) 
        { 
            cout << "Base::fun(), x = " << x << endl; 
        } 
}; 

class Derived : public Base 
{ 
    public: 
        virtual void fun ( int x=20 ) 
        { 
            cout << "Derived::fun(), x = " << x << endl; 
        } 
}; 


int main() 
{ 
    Derived d1; 
    Base *bp = &d1; 
    bp->fun();  // result:Derived::fun(), x = 10
    return 0; 
} 
```



### 1.3.5构造函数
1.构造函数可以被重载，实参决定使用哪个构造函数，构造函数自动执行，用于const对象的构造函数。
2.构造函数多一个初始化列表，在初始化列表中对类成员进行初始化，而在构造函数体里只是对成员进行赋值。如果初始化列表里没有，会调用该类型的默认构造函数进行初始化，然后在函数体里被重新赋值。
3.初始化const或引用类型数据成员的唯一机会在构造函数初始化列表中。
```c++
class ConstRef {
public:
	ConstRef(int ii);
private:
	int i;
	const int ci;  //只能在初始化时进行赋值
	int &ri;  //只能在初始化时进行赋值
};
ConstRef::ConstRef(int ii):i(ii),ci(i),ri(ii){}
```

4.构造函数初始化列表仅指定用于初始化成员的值，并不指定这些初始化执行的次序。成员被初始化的次序就是定义成员的次序。
5.explicit 修饰构造函数时，可以防止隐式转换和复制初始化


### 1.3.6析构函数
1.基类的析构函数必须为虚函数，在实现多态时，当用基类操作派生类，在析构时防止只析构基类而不析构派生类的状况发生。


### 1.3.7友元
友元提供了一种 普通函数或者类成员函数 访问另一个类中的私有或保护成员 的机制， 能访问私有成员 - 破坏封装性 - 友元关系不可传递 - 友元关系的单向性 - 友元声明的形式及数量不受限制
