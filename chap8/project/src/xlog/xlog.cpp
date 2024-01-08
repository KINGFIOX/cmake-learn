//////////////////////////////////  @��Ȩ˵��  //////////////////////////////////////////////////
///						Jiedi(China nanjing)Ltd.
/// @��Ȩ˵�� ����Ϳγ̰�Ȩ���Ĳܿ���ӵ�в��Ѿ���������Ȩ���˴��������Ϊѧϰ�ο���������Ŀ��ʹ�ã�
/// �γ����漰����������Դ����������������Ӧ����Ȩ
/// �γ�Դ�벻����ֱ��ת�ص������Ĳ��ͣ�������������ƽ̨�������������������߿γ̡�
/// �γ����漰����������Դ����������������Ӧ����Ȩ  @@
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  Դ��˵��  //////////////////////////////////////////////////
/// ��Ŀ����: CMake��������c++��Ŀ
/// ����   : 			    http://blog.csdn.net/jiedichina
/// ��Ѷ����			    https://jiedi.ke.qq.com/
/// ѧ��				    ���� �Ĳܿ�
/// ���Ŀ���			    http://cppds.com
/// CMake�ֲ�    	        http://cmake.org.cn
/// �����������γ�qqȺ ��296249312����ͬѧ����
/// ��ӭ���Ĳܿ���ʦ��΢�ţ�cppxcj
/// �������Ŀ���Ⱥ��296249312��ֱ����ϵȺ��ͷ����ؿγ�����
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// �γ̽���qqȺ296249312 //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////// COMMENT ///////////////////////////////////////////////

#include "xlog.h"
#include "xlog_thread.h"
#include <iomanip>
#include <memory>
#include <sstream>
#include <time.h>

using namespace std;

_XCPP_NAMESPACE_

// static std::shared_ptr<xcpp::XLogThread> xt;
unique_ptr<XWrite> XLogMessage::write_;
// bool is_log_init = false;
/*DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL*/
static const char* LogLevelName[] {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
};

// ֻ�ڲ���ʱ��
bool CloseXLog()
{

    // if (!xt)
    //	return false;
    // xt->Stop();
    XLogMessage::set_write(nullptr);
    // xt.reset();
    return true;
}
bool InitXLog(const char* appname, const char* logpath, const char* filename)
{
    cout << "Init XLog appname = " << appname << " path = " << logpath << endl;

    /*	{
                    std::unique_ptr<xcpp::XLogThread> xt(new XLogThread());
                    xt->Init(logpath, filename);

                    xt->Start();
                    xt->Stop();
            }
            auto xt2 = new xcpp::XLogThread();
            xt2->Init(logpath, filename);
            xt2->Start();
            this_thread::sleep_for(100ms);
            xt2->Stop();
            delete xt2;*/
    // xt.reset(new xcpp::XLogThread());
    unique_ptr<XLogThread> xt(new XLogThread());
    if (!xt->Init(logpath, filename))
        return false;
    xt->Start();
    // ostringstream ss;
    XLogMessage::set_write(move(xt));
    return true;
}
XLogMessage::~XLogMessage()
{
    // stream_.str();
    // cout << stream_.str();
    if (write_)
        write_->Write(stream_.str().c_str());
}

XLogMessage::XLogMessage(const char* file, int line, LogLevel level)
{
    auto time_now = chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(time_now);

    auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());

    tm tt;
// ��ʱ��ʱ��
#if _WIN32
    ::localtime_s(&tt, &t);
#else
    ::localtime_r(&t, &tt);
#endif

    // stream_ << file << line << (int)level;
    LogLevelName[1];
    int le = static_cast<int>(level);

    stream_ << "[" << LogLevelName[le] << ' ' << setfill('0')
            << setw(4) << tt.tm_year + 1900 << "-"
            << setw(2) << tt.tm_mon + 1 << "-"
            << setw(2) << tt.tm_mday
            << ' '
            << setw(2) << tt.tm_hour << ':'
            << setw(2) << tt.tm_min << ':'
            << setw(2) << tt.tm_sec << '.'
            << setw(6) << (int)((duration_in_ms % 1000).count())
            << ' '
            << setfill(' ') << " (" << this_thread::get_id() << ")" << setfill('0')
            << ' '
            << file << ':' << line << "] ";
}

XLogMessage::XLogMessage()
{
}

_END_NAMESPACE_