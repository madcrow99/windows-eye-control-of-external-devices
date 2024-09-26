using System;
using System.Collections.Generic;
using System.IO.Ports;
using Windows.UI.Xaml.Automation;

namespace FPS_game_controller
{ 
public class ButtonCommandMapper
{
    private Dictionary<string, string> buttonCommandMap;
    private SerialPort serialPort;

    public ButtonCommandMapper(string serialPortName)
    {
        // Initialize the serial port
        serialPort = new SerialPort(serialPortName, 9600);
        serialPort.Open();

        // Initialize the button-command map
        buttonCommandMap = new Dictionary<string, string>
        {
            //mouse movements I will use 48
            {"LLLFFF","MLLLFFF"}, {"LLFFF","MLLFFF"}, {"LFFF","MLFFF"}, {"FFF","MFFF"}, {"RFFF","MRFFF"}, {"RRFFF","MRRFFF"}, {"RRRFFF","MRRRFFF"},
            {"LLLFF","MLLLFF"}, {"LLFF","MLLFF"}, {"LFF","MLFF"}, {"FF","MFF"}, {"RFF","MRFF"}, {"RRFF","MRRFF"}, {"RRRFF","MRRRFF"},
            {"LLLF","MLLLF"}, {"LLF","MLLF"}, {"LF","MLF"}, {"FWD","MF"}, {"RF","MRF"}, {"RRF","MRRF"}, {"RRRF","MRRRF"},

            {"LLL","MLLL"}, {"LL","MLL"}, {"LFT","ML"}, {"RHT","MR"}, {"RR","MRR"}, {"RRR","MRRR"},
           
            {"LLLBBB","MLLLBBB"}, {"LLBBB","MLLBBB"}, {"LBBB","MLBBB"}, {"BBB","MBBB"}, {"RBBB","MRBBB"}, {"RRBBB","MRRBBB"}, {"RRRBBB","MRRRBBB"},
            {"LLLBB","MLLLBB"}, {"LLBB","MLLBB"}, {"LBB","MLBB"}, {"BB","MBB"}, {"RBB","MRBB"}, {"RRBB","MRRBB"}, {"RRRBB","MRRRBB"},
            {"LLLB","MLLLB"}, {"LLB","MLLB"}, {"LB","MLB"}, {"BWD","MB"}, {"RB","MRB"}, {"RRB","MRRB"}, {"RRRB","MRRRB"},

            //mouse buttons 
            {"MouseLeft", "MLeft" }, {"MouseRight", "MRight" }, {"MouseCenter", "MCenter" }, {"Scrolldown", "MScrolld"}, {"Scrollup", "MScrollu"},

            // Add other button-command mappings here
            // Uppercase alphabetic keys
            {"A", "KA"}, {"B", "KB"}, {"C", "KC"}, {"D", "KD"}, {"E", "KE"},
            {"F", "KF"}, {"G", "KG"}, {"H", "KH"}, {"I", "KI"}, {"J", "KJ"},
            {"K", "KK"}, {"L", "KL"}, {"M", "KM"}, {"N", "KN"}, {"O", "KO"},
            {"P", "KP"}, {"Q", "KQ"}, {"R", "KR"}, {"S", "KS"}, {"T", "KT"},
            {"U", "KU"}, {"V", "KV"}, {"W", "KW"}, {"X", "KX"}, {"Y", "KY"},
            {"Z", "KZ"},

            // Lowercase alphabetic keys
            {"a", "Ka"}, {"b", "Kb"}, {"c", "Kc"}, {"d", "Kd"}, {"e", "Ke"},
            {"f", "Kf"}, {"g", "Kg"}, {"h", "Kh"}, {"i", "Ki"}, {"j", "Kj"},
            {"k", "Kk"}, {"l", "Kl"}, {"m", "Km"}, {"n", "Kn"}, {"o", "Ko"},
            {"p", "Kp"}, {"q", "Kq"}, {"r", "Kr"}, {"s", "Ks"}, {"t", "Kt"},
            {"u", "Ku"}, {"v", "Kv"}, {"w", "Kw"}, {"x", "Kx"}, {"y", "Ky"},
            {"z", "Kz"},

            // Numeric keys
             {"0", "K0"}, {"ZERO", "K0"}, {"1", "K1"}, {"2", "K2"}, {"3", "K3"}, {"4", "K4"},
            {"5", "K5"}, {"6", "K6"}, {"7", "K7"}, {"8", "K8"}, {"9", "K9"},

            // Function keys
            {"F1", "KF1"}, {"F2", "KF2"}, {"F3", "KF3"}, // ... Continue for all function keys

            // Control keys
            {"Enter", "Kenter"}, {"Space", "Kspace"}, {"Tab", "Ktab"},
    
            // Arrow keys
            {"ArrowUp", "Kup"}, {"ArrowDown", "Kdown"}, {"ArrowLeft", "Kleft"}, {"ArrowRight", "Kright"},
        
            // Modifier keys
            {"Shift", "Kshift"}, {"Control", "Kcontrol"}, {"Alt", "Kalt"},

            // Special keys
            {"Esc", "Kescape"}, {"Backspace", "Kbackspace"}, {"NumLock", "Knumlock"}, {"CapsLock", "Kcapslock"},
            

            // Custom commands
            {"LatchCommand", "L"}, {"KeyLatchCommand", "N"},

            //gameplay commands
            {"GameLF", "GLF"}, {"GameLFF", "GLFF"}, {"GameFF", "GFF"}, {"GameRFF", "GRFF"}, {"GameRF", "GRF"},{"GameJump", "GJump"},
            {"GameLatch","GLatch"}, /* rotate left, left click, rotate right, Melee */
            {"GameSneak","GSneak"}, {"GameStrafeL","GStrafeL"}, {"GameBB","GBB"}, {"GameStrafeR","GStrafeR"}, {"GameSprint","GSprint"},
               
            //roblox commands
            {"robloxLF", "RLF"}, {"robloxLFF", "RLFF"}, {"robloxFF", "RFF"}, {"robloxRFF", "RRFF"}, {"robloxRF", "RRF"},
            {"robloxLatch","RLatch"}, /* rotate left, left click, rotate riRht, Melee */
            {"robloxSneak","RSneak"}, {"robloxStrafeL","RStrafeL"}, {"robloxBB","RBB"}, {"robloxStrafeR","RStrafeR"}, {"robloxSprint","RSprint"},
        };

        
    }

    public void SendCommandForButton(string buttonName)
    {
        if (buttonCommandMap.TryGetValue(buttonName, out string command))
        {
                // Assuming 'command' is a string containing your command
                byte[] commandBytes = System.Text.Encoding.ASCII.GetBytes(command);
                serialPort.Write(commandBytes, 0, commandBytes.Length);

                // Send the command over serial
                //serialPort.Write(command);
        }
        else
        {
            Console.WriteLine($"Command for button '{buttonName}' not found.");
        }
    }

    // Call this method to close the serial port when done
    public void Close()
    {
        if (serialPort != null && serialPort.IsOpen)
        {
            serialPort.Close();
        }
    }
}
    }