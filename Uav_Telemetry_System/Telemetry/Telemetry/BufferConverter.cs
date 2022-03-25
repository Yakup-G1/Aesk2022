﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Int8 = System.SByte;
using UInt8 = System.Byte;

namespace Telemetry
{
    class BufferConverter
    {

        public delegate void DecodeReceivedBuffer(); // why ???

        public static UInt32 ConvertToInt24(byte[] receivedBuffer, ref int startingIndex)      // aynen kardeşim 24 bit
        {
            byte[] veri = new byte[4];

            UInt32 fullData = BitConverter.ToUInt32(receivedBuffer, startingIndex);
            veri = BitConverter.GetBytes(fullData);
            UInt32 extra = (UInt8)BitConverter.ToChar(receivedBuffer, startingIndex+3);
            extra = (UInt32)extra << 24;
            UInt32 returnData = fullData - extra;
            startingIndex += 3;

            return returnData;
        }

        public static UInt8 ConvertToUInt8(byte[] receivedBuffer, ref int startingIndex)
        {
            UInt8 returnData = (UInt8)BitConverter.ToChar(receivedBuffer, startingIndex);
            startingIndex += sizeof(UInt8);
            return returnData;
        }

        public static Int8 ConvertToInt8(byte[] receivedBuffer, ref int startingIndex)
        {
            Int8 returnData = (Int8)BitConverter.ToChar(receivedBuffer, startingIndex);
            startingIndex += sizeof(Int8);
            return returnData;
        }

        public static UInt16 ConvertToUInt16(byte[] receivedBuffer, ref int startingIndex)
        {
            UInt16 returnData = BitConverter.ToUInt16(receivedBuffer, startingIndex);
            startingIndex += sizeof(UInt16);
            return returnData;
        }

        public static Int16 ConvertToInt16(byte[] receivedBuffer, ref int startingIndex)
        {
            Int16 returnData = BitConverter.ToInt16(receivedBuffer, startingIndex);
            startingIndex += sizeof(Int16);
            return returnData;
        }

        public static UInt32 ConvertToUInt32(byte[] receivedBuffer, ref int startingIndex)
        {
            UInt32 returnData = BitConverter.ToUInt32(receivedBuffer, startingIndex);
            startingIndex += sizeof(UInt32);
            return returnData;
        }

        public static Int32 ConvertToInt32(byte[] receivedBuffer, ref int startingIndex)
        {
            Int32 returnData = BitConverter.ToInt32(receivedBuffer, startingIndex);
            startingIndex += sizeof(Int32);
            return returnData;
        }

        public static UInt64 ConvertToUInt64(byte[] receivedBuffer, ref int startingIndex)
        {
            UInt64 returnData = BitConverter.ToUInt64(receivedBuffer, startingIndex);
            startingIndex += sizeof(UInt64);
            return returnData;
        }

        public static Int64 ConvertToInt64(byte[] receivedBuffer, ref int startingIndex)
        {
            Int64 returnData = BitConverter.ToInt64(receivedBuffer, startingIndex);
            startingIndex += sizeof(Int64);
            return returnData;
        }

        public static float ConvertToFloat(byte[] receivedBuffer, ref int startingIndex)
        {
            float returnData = (float)BitConverter.ToSingle(receivedBuffer, startingIndex);
            startingIndex += sizeof(float);
            return returnData;
        }

        public static double ConvertToDouble(byte[] receivedBuffer, ref int startingIndex)
        {
            double returnData = BitConverter.ToDouble(receivedBuffer, startingIndex);
            startingIndex += sizeof(double);
            return returnData;
        }

        public static float ConvertU16ToFloat(byte[] receivedBuffer, ref int startingIndex)
        {
            UInt16 receivedNumber = BitConverter.ToUInt16(receivedBuffer, startingIndex);
            float returnData = Convert.ToSingle(receivedNumber);
            startingIndex += sizeof(UInt16);
            return returnData;
        }

        public static double ConvertU32ToDouble(byte[] receivedBuffer, ref int startingIndex)
        {
            UInt32 receivedNumber = BitConverter.ToUInt32(receivedBuffer, startingIndex);
            double returnData = Convert.ToDouble(receivedNumber);
            startingIndex += sizeof(UInt32);
            return returnData;
        }

    }
}