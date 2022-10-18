#pragma once
#include <msclr/gcroot.h>
#include <msclr/marshal.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/cvconfig.h>

using namespace msclr;
using namespace msclr::interop;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace CPPCLISample 
{
	class MainHandler
	{
	private:

	public:
		MainHandler();
		//static MainHandler* m_pThisInst;

		bool m_bRunning;
		//gcroot<String ^> m_ManStringMsg;
		cv::String m_cvStringMSG;
		void RunSampleCPPEvent(gcroot<String^> fileName, double alpha, double beta, cv::Mat &SrcImg, cv::Mat &TarImg);
	};

	public ref class CLIInterfaceSample
	{
	public:
		CLIInterfaceSample();
		~CLIInterfaceSample();
		!CLIInterfaceSample();

		String^ nativeClassMsg;
		void RunSampleEvent(String^ imageFileName, double alpha, double beta);
		array<System::Byte>^ GetSourceImageData();
		array<System::Byte>^ GetTargetImageData();
		int ImageLength;
		int ImageWidth;
		int ImageHeight;
	private:
		MainHandler* mainProc;
		cv::Mat* SourceImage;
		cv::Mat* TargetImage;
	};
}
