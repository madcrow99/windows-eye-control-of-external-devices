using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace FPS_game_controller
{

    // MainPage class
    public sealed partial class MainPage : Page
    {
        private ButtonCommandMapper commandMapper;
        private bool latch_active = false;
        public MainPage()
        {
            this.InitializeComponent();

            // Initialize commandMapper with your serial port
            commandMapper = new ButtonCommandMapper("COM5"); 
            //Button_Content();
        }

        // Example button click event handler
        private void MyButton_Click(object sender, RoutedEventArgs e)
        {
            // Send the command associated with the button
            var button = sender as Button;
            if (button != null)
            {
                commandMapper.SendCommandForButton(button.Name);
                if (button.Name == "LatchCommand")
                {
                    if (latch_active == false)
                    {
                        latch_active = true;
                        //change background color to green
                        LatchCommand.Background = new SolidColorBrush(Windows.UI.Colors.Green);
                        LatchCommand.Content = "Latch Active";
                    }
                    else
                    {
                        latch_active = false;
                    //change background color to transparent
                        LatchCommand.Background = new SolidColorBrush(Windows.UI.Colors.Transparent);
                        LatchCommand.Content = "Latch Inactive";
                    }
                }
            }
        }
        //this for characters entered in the textbox 
        private void serialTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            if (textBox.Text.Length > 0)
            {
                string characterTyped = textBox.Text;

                // Send over serial
                commandMapper.SendCommandForButton(characterTyped);

                // Clear the TextBox
                textBox.Text = "";
            }
        }
        private void serialTextBox_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            // Check for special keys
            string command = null;
            switch (e.Key)
            {
                case Windows.System.VirtualKey.Enter:
                    command = "Enter";
                    break;
                case Windows.System.VirtualKey.Back:
                    command = "Backspace";
                    break;
                case Windows.System.VirtualKey.Tab:
                    command = "Tab";
                    break;
                /*case Windows.System.VirtualKey.Shift:
                    command = "Shift";
                    break;*/
                case Windows.System.VirtualKey.Control:
                    command = "Control";
                    break;
                case Windows.System.VirtualKey.Space:
                    command = "Space";
                    break;
                case Windows.System.VirtualKey.Escape:
                    command = "Esc";
                    break;
                case Windows.System.VirtualKey.Up:
                    command = "ArrowUp";
                    break;
                case Windows.System.VirtualKey.Down:
                    command = "ArrowDown";
                    break;
                case Windows.System.VirtualKey.Left:
                    command = "ArrowLeft";  
                    break;
                case Windows.System.VirtualKey.Right:
                    command = "ArrowRight";
                    break;

                    // Add cases for other special keys as needed
            }

            if (command != null)
            {
                // Send the special key command over serial
                commandMapper.SendCommandForButton(command);
            }
        }

        private void Button_Content()
        {
            //LLLFFF.Content = "LLLFFF";
            //LLFFF.Content = "LLFFF";    
            //LFFF.Content = "LFFF";
            //FFF.Content = "FFF";
            //RFFF.Content = "RFFF";
            //RRFFF.Content = "RRFFF";
            //RRRFFF.Content = "RRRFFF";
                    
            //LLLFF.Content = "LLLFF";
            LLFF.Content = "LLFF";
            //LFF.Content = "LFF";
            FF.Content = "FF";
            //RFF.Content = "RFF";
            RRFF.Content = "RRFF";
            //RRRFF.Content = "RRRFF";

            //LLLF.Content = "LLLF";
            //LLF.Content = "LLF";
            LF.Content = "LF";
            FWD.Content = "FWD";
            RF.Content = "RF";
            //RRF.Content = "RRF";
            //RRRF.Content = "RRRF";

            //LLL.Content = "LLL";
            LL.Content = "LL";
            LFT.Content = "LFT";
            RHT.Content = "RHT";
            RR.Content = "RR";
            //RRR.Content = "RRR";

            //LLLBBB.Content = "LLLBBB";
            //LLBBB.Content = "LLBBB";
            //LBBB.Content = "LBBB";
            //BBB.Content = "BBB";
            //RBBB.Content = "RBBB";
            //RRBBB.Content = "RRBBB";
            //RRRBBB.Content = "RRRBBB";

            //LLLBB.Content = "LLLBB";
            LLBB.Content = "LLBB";
            //LBB.Content = "LBB";
            BB.Content = "BB";
            //RBB.Content = "RBB";
            RRBB.Content = "RRBB";
            //RRRBB.Content = "RRRBB";
            
            //LLLB.Content = "LLLB";
            //LLB.Content = "LLB";
            LB.Content = "LB";
            BWD.Content = "BWD";
            RB.Content = "RB";
            //RRB.Content = "RRB";
            //RRRB.Content = "RRRB";
                



        }
        private void Misc_Click(object sender, RoutedEventArgs e)
        {
            commandMapper.Close();
            this.Frame.Navigate(typeof(misc));
        }
        private void Gameplay_Click(object sender, RoutedEventArgs e)
        {
            commandMapper.Close();
            this.Frame.Navigate(typeof(Gameplay));
        }

        private void Starship_Click(object sender, RoutedEventArgs e)
        {
            commandMapper.Close();
            this.Frame.Navigate(typeof(Starship));
        }


        // Clean up resources
        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            commandMapper.Close();
            base.OnNavigatedFrom(e);
        }
    }

}
