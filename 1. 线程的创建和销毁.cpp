error C2664: ��CreateThread��: ���ܽ����� 4 �ӡ�int��ת��Ϊ��LPVOID��
IntelliSense: "int" ���͵�ʵ���� "LPVOID" ���͵��ββ�����
��ʵ��ת����void*���;Ϳ�����
#include<iostream>
#include<windows.h>
using namespace std;
/*
* һ��˯��һ��׬Ǯ 
* ����һ������ -- �߳� 
* ����֪ʶ
* 1) ���̵ĸ���  ���ڵĲ���ϵͳ, ͬʱ����һ������  , �������ж�� , ֮ǰʹ�ó���������Ӧ��

��Ļ�����Ĳ���ʱ��: 2021/12/14 13:13


* �ó�������Ӧ�ò�����. �����˽��� , ����������Ӧ�� 
* ʲô�ǽ���? �����Ǿ���һ���������ܵĳ�����һЩ���ݼ����ϵ�һ�ζ�ִ̬�й��� .
* �����Ǿ�̬�� , �����Ƕ�̬�� 
* �������, �������м������ݵ��ڴ�, Ȼ���ڴ��д洢���������Լ�һ��һ����ָ��, 
* Ȼ������ִ��ָ��, ��ɶ�̬��ִ�й��� , ���ǽ��� 
* ��������̵Ĺ�ϵ ? 
* ͨ�����ִ�� , һ����������ж������ ,ͨ������, һ�����̿����ж������ 
* 
* 2) ��һ�� �˽��߳�
* ʲô���߳�? �������̵߳Ĺ�ϵ?
* ���� �����ڹ���, ��ϵͳ������Դ�Ļ�����Ԫ
* �߳� �����ڹ����еĹ���, ��cpu���Ⱥ�ִ�й����Ļ�����Ԫ
*  һ�����̿����ж���̵߳�. 
* 3) ΪʲôҪʹ���߳�? ����"ͬʱ"�������
* 4) ����߳������ִ�е�? ������ִ�� 
*  �����벢�� : ����, ָ��ͬ��ʱ����, ����ִ��    ����ָͬʱִ��.
* 5) ����߳�����ε���? ʱ��Ƭ�ֻ� 
* 6) ��ô����һ���߳�?  �߳� thread  �����߳� CreateThread 
* 7)�̵߳Ľ�һ�����
* �߳�  Ҫִ�е����������̺߳���������, �̺߳����˳�, �߳�ջ���� , �̻߳�����
* �̵߳Ĵ洢ʹ���߳�ջ�����, Ĭ�ϴ�С1MB 
* �̹߳������ù���������������� �̹߳���,���������+1 , �ָ��߳� �������-1(Ϊ0�����ٱ仯),�������Ϊ0,�ָ��߳�����
* ÿһ�ζ�createThread�����ĳɹ�����, ϵͳ�ͻ����ڲ�Ϊ�µ��̷߳���һ���ں˶���. 
* �ں˶���ʵ�ֹ����̵߳ĺ��� , �þ��, ���ǿ��Եõ��ں˶���. 
* �ں˶������ṩ���û���ϵͳ�ں�֮�佻���Ľӿ�.�ں˶���������������,�ں˶���ʹ�ü�����,�Լ��߳�������(cpu�Ĵ���״̬)��
* ��ô�����ں˶���?  ������һ���߳�, �ں˶���ʹ�ü���Ϊ2 , ��ر�ʹ�ü���Ҫ��0 , �رվ�� ʹ�ü���-1 �߳����� ʹ�ü���-1
* ʹ�ü�����0 , �ں˶�������
* �ڶ��������̵߳ķ���  TerminateThread();
*/
bool isquit = false;
//�̺߳��� -- ׬Ǯ
DWORD WINAPI ThreadProc( LPVOID lpParameter ){
	long count = (long)lpParameter;
	for( int i = 1 ; i < count ; ++i ){
		cout<< "׬��"<<i <<"Ԫ"<<endl;
		Sleep(100); // ���Ϊ 100ms ��ʹ��ʱ��Ƭ,ʲôʱ��ʼʹ��,Ҫ�ȵ�cpu���� һ������ʱ������趨ֵ
	}
	while(!isquit){
		Sleep(100);
		while(1){ Sleep(100); }
	}
	return 0;
}

int  main()
{
	//�����߳�
	HANDLE handle =  CreateThread(
					NULL, //  LPSECURITY_ATTRIBUTES lpThreadAttributes, ��ȫ�ȼ�������
					0 , //  SIZE_T dwStackSize, �߳�ջ�Ĵ�С Ĭ��1MB
					&ThreadProc, // LPTHREAD_START_ROUTINE lpStartAddress, // �̺߳����ĵ�ַ
					(void*)80, // LPVOID lpParameter, // ���ݵĲ���
					CREATE_SUSPENDED, //  DWORD dwCreationFlags, //�����̵߳ĳ�ʼ״̬ 0 ����ִ�� CREATE_SUSPENDED �Թ���̬����
					NULL); //  LPDWORD lpThreadId �߳�id

	//SuspendThread( handle ); //�����̺߳���
	//ResumeThread( handle ); // �ָ��̺߳���, ����̹߳���
	//ResumeThread( handle ); // �ָ��̺߳���, ����̹߳���
	//SuspendThread( handle ); //�����̺߳���

	int i = 0;
	while(1){
		Sleep(1000); //��ms����˯��
		i++;
		cout << "˯��" << i <<"��" <<endl;
		if( i == 3){
			ResumeThread( handle ); // �ָ��̺߳���, ����̹߳���
		}
		//if( i == 6){
		//	SuspendThread( handle ); //�����̺߳���
		//}
		if( i == 10 ) break;
	}
	cout << "˯����"<<endl;
	//ǿ��ɱ������
	//if( handle ){
	//	TerminateThread( handle , -1 ); // -1��ʾ�쳣�˳� 
	//}
        isquit = true;
	//�ȵȴ��߳��˳���Ȼ��ʱ�ˣ�����ǿ���˳��ķ�ʽ
	if(WAIT_TIMEOUT == WaitForSingleObject(handle,100)){
		 TerminateThread( handle , -1 );
	}
	//�رվ�� ʹ�ü���-1
	if( handle ){
		CloseHandle(handle);
		handle = NULL;
	}
	
	//getchar();
	system("pause");
	return 0;
}