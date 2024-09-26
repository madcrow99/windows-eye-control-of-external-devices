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
    public sealed partial class roblox : Page
    {
        private ButtonCommandMapper commandMapper;
        private bool latch_active = false;
        public roblox()
        {
            this.InitializeComponent();

            // Initialize commandMapper with your serial port
            commandMapper = new ButtonCommandMapper("COM5");

        }

        // Example button click event handler
        private void MyButton_Click(object sender, RoutedEventArgs e)
        {
            // Send the command associated with the button
            var button = sender as Button;
            if (button != null)
            {
                commandMapper.SendCommandForButton(button.Name);
                if (button.Name == "GameLatch")
                {
                    if (latch_active == false)
                    {
                        latch_active = true;
                        //change background color to green
                        GameLatch.Background = new SolidColorBrush(Windows.UI.Colors.Green);
                        GameLatch.Content = "Latch Active";
                    }
                    else
                    {
                        latch_active = false;
                        //change background color to transparent
                        GameLatch.Background = new SolidColorBrush(Windows.UI.Colors.Transparent);
                        GameLatch.Content = "Latch Inactive";
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
        private void Misc_Click(object sender, RoutedEventArgs e)
        {
            commandMapper.Close();
            this.Frame.Navigate(typeof(misc));
        }

        private void Shooting_Click(object sender, RoutedEventArgs e)
        {
            commandMapper.Close();
            this.Frame.Navigate(typeof(Shooting));
        }

        // Clean up resources
        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            commandMapper.Close();
            base.OnNavigatedFrom(e);
        }
    }

}
