// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� VCHECKERRESZHCN_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// VCHECKERRESZHCN_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef VCHECKERRESZHCN_EXPORTS
#define VCHECKERRESZHCN_API __declspec(dllexport)
#else
#define VCHECKERRESZHCN_API __declspec(dllimport)
#endif

// �����Ǵ� VCheckerResZhCn.dll ������
class VCHECKERRESZHCN_API CVCheckerResZhCn {
public:
	CVCheckerResZhCn(void);
	// TODO: �ڴ�������ķ�����
};

extern VCHECKERRESZHCN_API int nVCheckerResZhCn;

VCHECKERRESZHCN_API int fnVCheckerResZhCn(void);
