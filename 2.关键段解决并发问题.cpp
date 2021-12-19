#include<iostream>
#include<windows.h>
using namespace std;


//CRITICAL_SECTION
//�ؼ��εķ�װ -- һ���� , ������Դ���ʵ�Ȩ�޵�����
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

// С����  ���������߳�, ÿ���߳� ��ͬһ������nCount ��100��  --> Ԥ�����յĽ��Ӧ�ü�300��
int nCount = 0;
DWORD WINAPI ThreadProc( LPVOID lpParameter)
{
	for( int i = 0 ; i < 100 ; ++i)
	{
		Sleep(50);//
		g_lock.Lock();
		nCount++; // ����߳�ͬʱ���� nCount 
		g_lock.UnLock();
//�߳�1: nCount = 20 nCount++ --> 21
//�߳�2: nCount = 20 nCount++ --> 21    �ᵼ��һЩ++������Ч
		cout<< "nCount:" << nCount <<endl; 
		
		Sleep(50);
	}
	return 0;
}
//��������������������: ����̻߳����, ͬʱ��һ����Դ���ж�д����, �����½���������ִ�н����һ��
//�߳�ͬ�������������
//�߳�ͬ��: ͨ��Э���߳�ִ�е�˳��, �������߳�ͬʱ����ͬһ����Դ���²�������, ʹ������ִ�н��һ��.
//�����õ��߳�ͬ����ʽ: ԭ�ӷ���, �ؼ���, �¼�, ������, ��������, �ź���
//ʹ�ùؼ�������� 

int main()
{
	CreateThread(NULL,0, &ThreadProc , 0 , 0, NULL  );//��ȫ���� , ջ��С , ����ָ�� , ���� , ״̬, �߳�id
	CreateThread(NULL,0, &ThreadProc , 0 , 0, NULL  );
	CreateThread(NULL,0, &ThreadProc , 0 , 0, NULL  );
	//ThreadProc(0);
	//ThreadProc(0);
	//ThreadProc(0);

	system("pause");
	return 0;
}