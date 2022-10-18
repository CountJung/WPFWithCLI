using System;
using System.Windows;


namespace WPFWithCLI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //public CLIInterfaceSample? CLISampleTest { get; set; } 
        public MainWindow()
        {
            InitializeComponent();
            //CLISampleTest = new CLIInterfaceSample();
            DataContext = new MainViewModel();
            Closing += MainViewModel.Instance!.ClosingEvent;
        }

        private void CPPCLIEventButtonClick(object sender, RoutedEventArgs e)
        {
            //CLISampleTest?.RunSampleEvent(); 
        }

        protected override void OnClosed(EventArgs e)
        {
            //CLISampleTest?.Dispose();
            base.OnClosed(e);
        }
    }
}
