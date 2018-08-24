#include <windows.h>
#include <tchar.h>
#include "resource.h"

HWND hFirst, hSecond, hResult, hButton;
TCHAR first[20], second[20], result[20];
int first_n, second_n, res_n;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
		CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1);
		hFirst = GetDlgItem(hWnd, IDC_EDIT1);
		hSecond = GetDlgItem(hWnd, IDC_EDIT2);
		hResult = GetDlgItem(hWnd, IDC_EDIT3);
		hButton = GetDlgItem(hWnd, IDOK);

		return TRUE;
	case WM_COMMAND:
		if ((LOWORD(wParam) == IDC_EDIT1 || LOWORD(wParam) == IDC_EDIT2))
		{
			GetWindowText(hFirst, first, 20);
			GetWindowText(hSecond, second, 20);
			if (lstrlen(first) == 0 || lstrlen(second) == 6)
				EnableWindow(hButton, FALSE);
			else
				EnableWindow(hButton, TRUE);
		}
		if (LOWORD(wParam) == IDOK)
		{
			first_n = _wtof(first);
			second_n = _wtof(second);
			if (IsDlgButtonChecked(hWnd, IDC_RADIO1) == BST_CHECKED)
			{
				res_n = first_n + second_n;
			}
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO2) == BST_CHECKED)
			{
				res_n = first_n - second_n;
			}
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO3) == BST_CHECKED)
			{
				res_n = first_n * second_n;
			}
			else{
				if (second_n == 0)
				{
					MessageBox(hWnd, TEXT("На ноль делить нельзя!"), TEXT("Ошибка"), MB_OK | MB_ICONINFORMATION);
					return TRUE;
				}
				res_n = first_n / second_n;
			}


			wsprintf(result, TEXT("%d"), res_n);
			SetWindowText(hResult, result);
		}
		return TRUE;
	}
	return FALSE;
}