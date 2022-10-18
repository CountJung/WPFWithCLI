using CPPCLISample;
using Microsoft.Win32;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace WPFWithCLI
{
    public class MainViewModel : ViewModel
    {
        public static MainViewModel? Instance { get; set; }
        private string? resultMessage;
        public string? ResultMessage { get => resultMessage; set => Set(ref resultMessage, value, nameof(ResultMessage)); }
        public CLIInterfaceSample? CLISampleTest { get; set; }
        private WriteableBitmap? sourceImage;
        public WriteableBitmap? SourceImage { get => sourceImage; set => Set(ref sourceImage, value, nameof(SourceImage)); }
        private WriteableBitmap? targetImage;
        public WriteableBitmap? TargetImage { get => targetImage; set => Set(ref targetImage, value, nameof(TargetImage)); }
        private double? alphaParam;
        public double? AlphaParam { get => alphaParam; set => Set(ref alphaParam, value, nameof(AlphaParam)); }
        private double? betaParam;
        public double? BetaParam { get => betaParam; set => Set(ref betaParam, value, nameof(BetaParam)); }

        public MainViewModel()
        {
            Instance = this;
            CLISampleTest = new CLIInterfaceSample();
            CPPCLIEventCmd = new DelegateCommand(CPPCLIEventClick);
            AlphaParam = 3; BetaParam = 2;
        }

        public ICommand CPPCLIEventCmd { get; private set; }
        private void CPPCLIEventClick(object s)
        {
            OpenFileDialog fileDialog = new()
            {
                Multiselect = false,
                //InitialDirectory = "c:\\",
                Filter = "BitmapFiles|*.bmp|PNGFiles|*.png|JpegFiles|*.jpg"
            };
            if (fileDialog.ShowDialog() == true)
            {
                string imageFileName = fileDialog.FileName;
                CLISampleTest?.RunSampleEvent(imageFileName,(double)alphaParam!,(double)betaParam!);
                ResultMessage = CLISampleTest?.nativeClassMsg;
                byte[] Sourcedata = CLISampleTest!.GetSourceImageData();
                byte[] TargetData = CLISampleTest!.GetTargetImageData();
                SourceImage = ByteArrayToImage(Sourcedata);
                TargetImage = ByteArrayToImage(TargetData);
            }
        }
        public void ClosingEvent(object? sender, CancelEventArgs e)
        {
            CLISampleTest?.Dispose();
        }

        public WriteableBitmap ByteArrayToImage(byte[] Array)
        {
            var width = CLISampleTest!.ImageWidth;
            var height = CLISampleTest!.ImageHeight;
            var dpiX = 96d;
            var dpiY = 96d;
            var pixelFormat = PixelFormats.Bgr24;
            var bytesPerPixel = (pixelFormat.BitsPerPixel + 7) / 8;
            var stride = bytesPerPixel * width;

            var bitmap = BitmapSource.Create(width, height, dpiX, dpiY, pixelFormat, null, Array, stride);
            WriteableBitmap wbtmMap = new(bitmap);
            return wbtmMap;
        }
    }
}
