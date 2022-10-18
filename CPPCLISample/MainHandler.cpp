#include "MainHandler.h"

namespace CPPCLISample
{
	//MainHandler* MainHandler::m_pThisInst = nullptr;
	MainHandler::MainHandler()
	{
		//m_pThisInst = this;
	}

	void MainHandler::RunSampleCPPEvent(gcroot<String^> fileName, double alpha, double beta, cv::Mat& SrcImg, cv::Mat& TarImg)
	{
		char* arrFileName = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
		//pin_ptr<const wchar_t> strFileArr = PtrToStringChars(fileName);
		cv::Mat image = cv::imread(arrFileName); //"D:\\Work\\Library\\opencv-4.6.0\\sources\\samples\\data\\lena.jpg"
		cv::Mat enhance;
		Marshal::FreeHGlobal((IntPtr)arrFileName);

		//float fkernel[] = {-1,-1,-1,-1,9,-1,-1,-1,-1};
		//cv::Mat kernel(3, 3, CV_32F, fkernel);
		//cv::imshow("TestCV Show", image);
		//m_ManStringMsg = "testManageMessage";
		m_cvStringMSG = "OpenCV Gaussian Blur Defocusing";
		cv::GaussianBlur(image, enhance, cv::Size(0, 0), 3);
		cv::addWeighted(image, alpha, enhance, -beta, 0, enhance);
		//cv::imshow("Show enhance", enhance);
		//cv::filter2D(image, enhance ,-1, kernel);
		//cv::imshow("Show filter2D", enhance);
		SrcImg = image; TarImg = enhance;
	}

	CLIInterfaceSample::CLIInterfaceSample()
	{
		mainProc = new MainHandler();
		mainProc->m_bRunning = true;
		nativeClassMsg = gcnew String("");
		SourceImage = new cv::Mat();
		TargetImage = new cv::Mat();
	}

	CLIInterfaceSample::~CLIInterfaceSample() // managed, unmanaged ??
	{
		mainProc->m_bRunning = false;
		delete mainProc;
		mainProc = nullptr;
	}

	CLIInterfaceSample::!CLIInterfaceSample() //unmanaged
	{
		mainProc->m_bRunning = false;
		delete mainProc;
		mainProc = nullptr;
	}

	void CLIInterfaceSample::RunSampleEvent(String^ imageFileName, double alpha, double beta)
	{
		cv::Mat SrcImg, TarImg;
		mainProc->RunSampleCPPEvent(imageFileName,alpha,beta, SrcImg,TarImg);
		if (!SourceImage->empty()) SourceImage->release();
		if (!TargetImage->empty()) TargetImage->release();
		SrcImg.copyTo(*SourceImage);
		TarImg.copyTo(*TargetImage);
		ImageLength = SourceImage->rows * SourceImage->cols * SourceImage->channels();
		ImageHeight = SourceImage->rows; ImageWidth = SourceImage->cols;
		//nativeClassMsg = mainProc->m_ManStringMsg;
		nativeClassMsg = gcnew String(mainProc->m_cvStringMSG.c_str());
	}

	array<Byte>^ CLIInterfaceSample::GetSourceImageData()
	{
		// TODO: 여기에 return 문을 삽입합니다.
		array<Byte>^ sourceDataArray = gcnew array<Byte>(ImageLength);
		Marshal::Copy((IntPtr)SourceImage->ptr(), sourceDataArray, 0, ImageLength);
		return sourceDataArray;
	}

	array<Byte>^ CLIInterfaceSample::GetTargetImageData()
	{
		// TODO: 여기에 return 문을 삽입합니다.
		array<Byte>^ targetDataArray = gcnew array<Byte>(ImageLength);
		Marshal::Copy((IntPtr)TargetImage->ptr(), targetDataArray, 0, ImageLength);
		return targetDataArray;
	}
	
}
