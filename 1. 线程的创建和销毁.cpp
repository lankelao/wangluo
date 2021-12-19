error C2664: “CreateThread”: 不能将参数 4 从“int”转换为“LPVOID”
IntelliSense: "int" 类型的实参与 "LPVOID" 类型的形参不兼容
把实参转化成void*类型就可以了
#include<iostream>
#include<windows.h>
using namespace std;
/*
* 一边睡觉一边赚钱 
* 引进一个概念 -- 线程 
* 背景知识
* 1) 进程的概念  早期的操作系统, 同时运行一个程序  , 后来运行多个 , 之前使用程序来描述应用

屏幕剪辑的捕获时间: 2021/12/14 13:13


* 用程序描述应用不合理. 定义了进程 , 用它来描述应用 
* 什么是进程? 进程是具有一定独立功能的程序在一些数据集合上的一次动态执行过程 .
* 程序是静态的 , 进程是动态的 
* 点击程序, 程序运行加载数据到内存, 然后内存中存储的是数据以及一条一条的指令, 
* 然后依次执行指令, 完成动态的执行过程 , 就是进程 
* 程序与进程的关系 ? 
* 通过多次执行 , 一个程序可以有多个进程 ,通过调用, 一个进程可以有多个程序 
* 
* 2) 进一步 了解线程
* 什么是线程? 进程与线程的关系?
* 进程 类似于工厂, 是系统分配资源的基本单元
* 线程 类似于工厂中的工人, 是cpu调度和执行工作的基本单元
*  一个进程可以有多个线程的. 
* 3) 为什么要使用线程? 可以"同时"完成任务
* 4) 多个线程是如何执行的? 并发的执行 
*  并发与并行 : 并发, 指相同的时间间隔, 交替执行    并行指同时执行.
* 5) 多个线程是如何调度? 时间片轮换 
* 6) 怎么创建一个线程?  线程 thread  创建线程 CreateThread 
* 7)线程的进一步理解
* 线程  要执行的任务是用线程函数描述的, 线程函数退出, 线程栈销毁 , 线程会销毁
* 线程的存储使用线程栈来完成, 默认大小1MB 
* 线程挂起是用挂起计数器来计数的 线程挂起,挂起计数器+1 , 恢复线程 挂起计数-1(为0不会再变化),挂起计数为0,恢复线程运行
* 每一次对createThread函数的成功调用, 系统就会在内部为新的线程分配一个内核对象. 
* 内核对象实现管理线程的函数 , 用句柄, 我们可以得到内核对象. 
* 内核对象是提供给用户与系统内核之间交互的接口.内核对象包含挂起计数器,内核对象使用计数器,以及线程上下文(cpu寄存器状态)等
* 怎么销毁内核对象?  当创建一个线程, 内核对象使用计数为2 , 想关闭使用计数要归0 , 关闭句柄 使用计数-1 线程销毁 使用计数-1
* 使用计数归0 , 内核对象销毁
* 第二种销毁线程的方法  TerminateThread();
*/
bool isquit = false;
//线程函数 -- 赚钱
DWORD WINAPI ThreadProc( LPVOID lpParameter ){
	long count = (long)lpParameter;
	for( int i = 1 ; i < count ; ++i ){
		cout<< "赚了"<<i <<"元"<<endl;
		Sleep(100); // 理解为 100ms 不使用时间片,什么时候开始使用,要等到cpu安排 一般休眠时间大于设定值
	}
	while(!isquit){
		Sleep(100);
		while(1){ Sleep(100); }
	}
	return 0;
}

int  main()
{
	//创建线程
	HANDLE handle =  CreateThread(
					NULL, //  LPSECURITY_ATTRIBUTES lpThreadAttributes, 安全等级的描述
					0 , //  SIZE_T dwStackSize, 线程栈的大小 默认1MB
					&ThreadProc, // LPTHREAD_START_ROUTINE lpStartAddress, // 线程函数的地址
					(void*)80, // LPVOID lpParameter, // 传递的参数
					CREATE_SUSPENDED, //  DWORD dwCreationFlags, //创建线程的初始状态 0 立即执行 CREATE_SUSPENDED 以挂起态创建
					NULL); //  LPDWORD lpThreadId 线程id

	//SuspendThread( handle ); //挂起线程函数
	//ResumeThread( handle ); // 恢复线程函数, 解除线程挂起
	//ResumeThread( handle ); // 恢复线程函数, 解除线程挂起
	//SuspendThread( handle ); //挂起线程函数

	int i = 0;
	while(1){
		Sleep(1000); //以ms级别睡眠
		i++;
		cout << "睡了" << i <<"秒" <<endl;
		if( i == 3){
			ResumeThread( handle ); // 恢复线程函数, 解除线程挂起
		}
		//if( i == 6){
		//	SuspendThread( handle ); //挂起线程函数
		//}
		if( i == 10 ) break;
	}
	cout << "睡醒了"<<endl;
	//强制杀死进程
	//if( handle ){
	//	TerminateThread( handle , -1 ); // -1表示异常退出 
	//}
        isquit = true;
	//先等待线程退出，然后超时了，采用强制退出的方式
	if(WAIT_TIMEOUT == WaitForSingleObject(handle,100)){
		 TerminateThread( handle , -1 );
	}
	//关闭句柄 使用计数-1
	if( handle ){
		CloseHandle(handle);
		handle = NULL;
	}
	
	//getchar();
	system("pause");
	return 0;
}