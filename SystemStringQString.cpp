#include "SystemStringQString.h"

#pragma unmanaged
#include <QString>
#pragma managed

using namespace System::Runtime::InteropServices;

std::wstring MarshalString(System::String^ s)
{
	using namespace System::Runtime::InteropServices;
	std::wstring ret;
	System::IntPtr p = Marshal::StringToHGlobalUni(s);
	if (p.ToPointer())
	{
		ret.assign((wchar_t const*)p.ToPointer());
		Marshal::FreeHGlobal(p);
	}
	return ret;
}

System::String^ q2ss(const QString &qstring)
{
	return gcnew System::String((const wchar_t *)qstring.utf16());
}

QString ss2q(System::String^ str)
{
	/* or ...
	using namespace msclr::interop;
	return QString::fromStdWString(marshal_as<std::wstring>(str));
	*/

	return QString::fromStdWString(MarshalString(str));
}