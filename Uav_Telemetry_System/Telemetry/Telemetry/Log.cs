using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Telemetry
{
    class Log
    {
        public string filePath;
        public string fileName;
        public string file;

        public Log(string path)
        {
            DateTime dt = DateTime.Now;
            string header = string.Empty;

            filePath = path;
            fileName = DateTime.Now.ToString("yyyy_MM_dd_HH_mm_ss") + ".txt"; ;

            file = filePath + fileName;

            header =  "Uçuş Süresi " + "\t" + "\t"
                    + "Pitch_Angle " + "\t" + "\t"
                    + "Roll_Angle " + "\t" + "\t"
                    + "Yaw_Angle " + "\t" + "\t" + "\t"
                    + "Altitude " + "\t" + "\t"
                    + "Motor1_PWM " + "\t" + "\t"
                    + "Motor2_PWM " + "\t" + "\t"
                    + "Motor3_PWM " + "\t" + "\t"
                    + "Motor4_PWM " + "\t" + "\t"
                    + "RollPitch_Kp  " + "\t" + "\t"
                    + "RollPitch_Ki " + "\t" + "\t"
                    + "RollPitch_Kd " + "\t" + "\t"
                    + "Yaw_Kp " + "\t" + "\t" + "\t"
                    + "Yaw_Ki " + "\t" + "\t" + "\t"
                    + "Yaw_Kd " + "\t" + "\t" + "\t"
                    + "Altitude_Kp " + "\t" + "\t"
                    + "Altitude_Ki " + "\t" + "\t"
                    + "Altitude_Kd " + "\t" + "\t";

            StreamWriter sw = new StreamWriter(file, append: false);

            sw.WriteLine(header);

            sw.Close();
        }

        public void WriteLine(string logtime)
        {
            string line
                = logtime   + "\t" + "\t" + RecieveData.pitch.ToString("0.00")
                            + "\t" + "\t" + "\t" + RecieveData.roll.ToString("0.00")
                            + "\t" + "\t" + "\t" + RecieveData.yaw.ToString("0.00")
                            + "\t" + "\t" + "\t" + "\t" + RecieveData.altitude.ToString("0.00")
                            + "\t" + "\t" + "\t" + RecieveData.motor1.ToString("0.000")
                            + "\t" + "\t" + RecieveData.motor2.ToString("0.000")
                            + "\t" + "\t" + RecieveData.motor3.ToString("0.000")
                            + "\t" + "\t" + RecieveData.motor4.ToString("0.000")
                            + "\t" + "\t" + RecieveData.RollPitch_Kp.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.RollPitch_Ki.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.RollPitch_Kd.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.Yaw_Kp.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.Yaw_Ki.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.Yaw_Kd.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.Altitude_Kp.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.Altitude_Ki.ToString("0.000")
                            + "\t" + "\t" + "\t" + RecieveData.Altitude_Kd.ToString("0.000");



            StreamWriter sw = new StreamWriter(file, append: true);

            sw.WriteLine(line);

            sw.Close();
        }
    }
}
