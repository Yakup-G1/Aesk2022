using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Telemetry
{
    class RecieveData
    {
        static public float RollPitch_Kp { get; set; }
        static public float RollPitch_Ki { get; set; }
        static public float RollPitch_Kd { get; set; }

        static public float Yaw_Kp { get; set; }
        static public float Yaw_Ki { get; set; }
        static public float Yaw_Kd { get; set; }

        static public float Altitude_Kp { get; set; }
        static public float Altitude_Ki { get; set; }
        static public float Altitude_Kd { get; set; }

        static public float GPS_Kp { get; set; }
        static public float GPS_Ki { get; set; }
        static public float GPS_Kd { get; set; }

        static public float Ext1_Kp { get; set; }
        static public float Ext1_Ki { get; set; }
        static public float Ext1_Kd { get; set; }

        static public float Ext2_Kp { get; set; }
        static public float Ext2_Ki { get; set; }
        static public float Ext2_Kd { get; set; }

        /// </>
        /// buraya kadarki değişkenler PID verileriydi. Alttakiler ise sürekli gelecek olan veriler.
        /// </>

        static public float roll { get; set; }
        static public float pitch { get; set; }
        static public float yaw { get; set; }
        static public float altitude { get; set; }
        static public UInt16 motor1 { get; set; }
        static public UInt16 motor2 { get; set; }
        static public UInt16 motor3 { get; set; }
        static public UInt16 motor4 { get; set; }
        static public float rollError { get; set; }
        static public float pitchError { get; set; }
        static public float yawError { get; set; }
        static public float altitudeError { get; set; }
        static public float batteryVoltage { get; set; }


        static public UInt16 adc1 { get; set; }
        static public UInt16 adc2 { get; set; }
        static public UInt16 adc3 { get; set; }
        static public UInt16 adc4 { get; set; }
        static public UInt16 adc5 { get; set; }
        static public UInt16 adc6 { get; set; }
        static public UInt16 adc7 { get; set; }
        static public UInt16 adc8 { get; set; }
        static public UInt16 adc9 { get; set; }
        static public UInt16 adc10 { get; set; }

        static public float LidarOutput { get; set; }

        static public float latitude { get; set; }
        static public float longitude { get; set; }
        static public UInt32 hAcc { get; set; }
        static public Int32 velN { get; set; }
        static public Int32 velE { get; set; }
        static public Int32 velD { get; set; }
        static public float gSpeed { get; set; }
        static public float SatelliteNumber { get; set; }




        public void DataPackRead(byte[] receiveBuffer)
        {
            int startingIndex;

            if (receiveBuffer[0] == 'P')
            {
                #region PID COEFFICIENTS
                startingIndex = 2;

                RollPitch_Kp = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                RollPitch_Ki = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                RollPitch_Kd = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;

                Yaw_Kp = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Yaw_Ki = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Yaw_Kd = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;

                Altitude_Kp = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Altitude_Ki = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Altitude_Kd = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;

                GPS_Kp = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                GPS_Ki = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                GPS_Kd = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;

                Ext1_Kp = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Ext1_Ki = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Ext1_Kd = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;

                Ext2_Kp = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Ext2_Ki = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;
                Ext2_Kd = (float)BufferConverter.ConvertToInt24(receiveBuffer, ref startingIndex) / 100000;

                //******************** Text'ler atanıyor ********************//

                UITools.SetPID.btnRxRollPitchKp.Text = RollPitch_Kp.ToString();
                UITools.SetPID.btnRxRollPitchKi.Text = RollPitch_Ki.ToString();
                UITools.SetPID.btnRxRollPitchKd.Text = RollPitch_Kd.ToString();

                UITools.SetPID.btnRxYawKp.Text = Yaw_Kp.ToString();
                UITools.SetPID.btnRxYawKi.Text = Yaw_Ki.ToString();
                UITools.SetPID.btnRxYawKd.Text = Yaw_Kd.ToString();

                UITools.SetPID.btnRxAltitudeKp.Text = Altitude_Kp.ToString();
                UITools.SetPID.btnRxAltitudeKi.Text = Altitude_Ki.ToString();
                UITools.SetPID.btnRxAltitudeKd.Text = Altitude_Kd.ToString();

                UITools.SetPID.btnRxGpsKp.Text = GPS_Kp.ToString();
                UITools.SetPID.btnRxGpsKi.Text = GPS_Ki.ToString();
                UITools.SetPID.btnRxGpsKd.Text = GPS_Kd.ToString();

                UITools.SetPID.btnRxExt1Kp.Text = Ext1_Kp.ToString();
                UITools.SetPID.btnRxExt1Ki.Text = Ext1_Ki.ToString();
                UITools.SetPID.btnRxExt1Kd.Text = Ext1_Kd.ToString();

                UITools.SetPID.btnRxExt2Kp.Text = Ext2_Kp.ToString();
                UITools.SetPID.btnRxExt2Ki.Text = Ext2_Ki.ToString();
                UITools.SetPID.btnRxExt2Kd.Text = Ext2_Kd.ToString();

                #endregion
            }

            else if(receiveBuffer[0] == 'G')
            {
                #region GPS BUFFER
                frmMission.crc16_dataRx = Form1.aeskCRCCalculate(receiveBuffer, (uint)Form1.bytesToReadCount);
                frmMission.GPS_Com_Flag = false;
                #endregion
            }

            else if(receiveBuffer[0] == 'A')
            {
                #region MAIN PACKET
                startingIndex = 2;

                yaw = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                roll = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                pitch = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                altitude = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex)/100;
                motor1 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex);
                motor2 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex);
                motor3 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex);
                motor4 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex);
                yawError = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                rollError = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                pitchError = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                altitudeError = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                batteryVoltage = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex);
                LidarOutput = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex);

                latitude = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                longitude = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                hAcc = BufferConverter.ConvertToUInt32(receiveBuffer, ref startingIndex);
                velN= BufferConverter.ConvertToInt32(receiveBuffer, ref startingIndex);
                velE = BufferConverter.ConvertToInt32(receiveBuffer, ref startingIndex);
                velD = BufferConverter.ConvertToInt32(receiveBuffer, ref startingIndex);
                gSpeed = BufferConverter.ConvertToFloat(receiveBuffer, ref startingIndex);
                SatelliteNumber = BufferConverter.ConvertToUInt8(receiveBuffer, ref startingIndex);

                //adc1 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc2 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc3 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc4 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc5 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc6 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc7 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc8 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc9 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                //adc10 = BufferConverter.ConvertToUInt16(receiveBuffer, ref startingIndex); 
                #endregion
            }

            else if(receiveBuffer[0] == 'U')
            {
                #region RESET
                MessageBox.Show(" System Reset Succesful");
                #endregion
            }

            else if(receiveBuffer[0] == 'E' && receiveBuffer[1] == 'R')
            {
                #region ERROR DETECTION
                //try
                //{
                //    counter++;
                //    if (counter == 100)
                //        counter = 10;
                //    System.Threading.Thread.Sleep(counter);

                //    if (frmSetPID.PID_Com_Flag)
                //    {
                //        Form1.serialPort1.Write(frmSetPID.PID_Transmit_Buffer, 0, frmSetPID.byteCounter);
                //    }
                //    else if (frmMission.GPS_Com_Flag)
                //    {
                //        Form1.serialPort1.Write(frmMission.GPS_Buffer, 0, frmMission.index);
                //    }
                //    else
                //    {

                //    }
                //}
                //catch (Exception)
                //{

                //}
                #endregion
            }

        }
    }

    
}
