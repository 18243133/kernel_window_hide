#include <windows.h>
#include <stdio.h>
#define HIDE_WINDOW CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _message64
{
	__int64 window_result;			// ִ�н��
	__int64 window_handle;			// ���ھ��
	int window_attributes;				// ��������
}message64;

void simple()
{
	HANDLE h = CreateFileW(L"\\\\.\\hide_windows", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (h == INVALID_HANDLE_VALUE) return;

	// �������ע���Ĵ���
	HWND window_handle = FindWindowW(L"RegEdit_RegEdit", 0);
	if (window_handle)
	{
		/*
		����������,����WDA_EXCLUDEFROMCAPTURE��ʶ��һЩ�°�Win10�ϲ���Ч��(��͸��)
		�ھɰ�Win10�ϱ���Ϊ��ɫ����,����û�а취������
		*/
		message64 info{ 0 };
		info.window_attributes = WDA_EXCLUDEFROMCAPTURE;
		info.window_handle = (__int64)window_handle;
		DeviceIoControl(h, HIDE_WINDOW, &info, sizeof(info), &info, sizeof(info), 0, 0);

		/*
		ע������,��������������WDA_EXCLUDEFROMCAPTURE��ʶ,��������Ҳ�Ƿ���0
		��һ��������Ҳ�ܸ����·�����ϵͳ��
		*/
		DWORD Style = 0;
		GetWindowDisplayAffinity(window_handle, &Style);
		printf("style is %d \n", Style);
	}

	CloseHandle(h);
}

int main(int argc, char* argv[])
{
	simple();
	system("pause");
	return 0;
}