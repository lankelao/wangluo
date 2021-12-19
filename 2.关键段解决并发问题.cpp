#include<iostream>
#include<windows.h>
using namespace std;


//CRITICAL_SECTION
//关键段的封装 -- 一种锁 , 对于资源访问的权限的限制
class MyLock
{
public:
	MyLock(){
		InitializeCriticalSection(&cs);
	}
	~MyLock(){
		DeleteCriticalSection(&cs);
	}
	void Lock(){
		EnterCriticalSection(&cs);
	}
	void UnLock(){
		LeaveCriticalSection(&cs);
	}
private:
	CRITICAL_SECTION cs;
};

MyLock  g_lock;

// 小例子  创建三个线程, 每个线程 对同一个变量nCount 加100次  --> 预期最终的结果应该加300次
int nCount = 0;
DWORD WINAPI ThreadProc( LPVOID lpParameter)
{
	for( int i = 0 ; i < 100 ; ++i)
	{
		Sleep(50);//
		g_lock.Lock();
		nCount++; // 多个线程同时操作 nCount 
		g_lock.UnLock();
//线程1: nCount = 20 nCount++ --> 21
//线程2: nCount = 20 nCount++ --> 21    会导致一些++操作无效
		cout<< "nCount:" << nCount <<endl; 
		
		Sleep(50);
	}
	return 0;
}
//上面的问题叫做并发问题: 多个线程或进程, 同时对一个资源进行读写操作, 而导致结果错误或多次执行结果不一致
//线程同步解决并发问题
//线程同步: 通过协调线程执行的顺序, 避免多个线程同时操作同一个资源导致并发问题, 使结果多次执行结果一致.
//常见得到线程同步方式: 原子访问, 关键段, 事件, 互斥量, 条件变量, 信号量
//使用关键段来解决 

int main()
{
	CreateThread(NULL,0, &ThreadProc , 0 , 0, NULL  );//安全描述 , 栈大小 , 函数指针 , 参数 , 状态, 线程id
	CreateThread(NULL,0, &ThreadProc , 0 , 0, NULL  );
	CreateThread(NULL,0, &ThreadProc , 0 , 0, NULL  );
	//ThreadProc(0);
	//ThreadProc(0);
	//ThreadProc(0);

	system("pause");
	return 0;
}