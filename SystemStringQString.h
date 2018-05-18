#ifndef SSQS_H
#define SSQS_H

#pragma unmanaged
#include <QString>
#pragma managed

#include <string>

std::wstring MarshalString(System::String^ s);
System::String^ q2ss(const QString &qstring);
QString ss2q(System::String^ str);

#endif