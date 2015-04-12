using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices; 

namespace CSharpDemo
{
    class Program
    {

        public delegate void TFNFindCallback (IntPtr buffer,int bufferCount, int totalCount,int ErrorCode);
        [DllImport("finderlib64.dll", EntryPoint = "FindW", CharSet = CharSet.Unicode)]
        public static extern   int Find64(String AStr,
									TFNFindCallback ACallback,
									String ADir, 
									String AExcludeDir,
									String AFilter,
									int ACount,
									int Afrom,
									bool ASpaceOr,
									bool AWholeWords,
									bool ACaseSensitive,
									bool AIncludeDir,
									bool AIncludeFiles,
									UInt16 ATimeoutMS);
        [DllImport("finderlib.dll", EntryPoint = "FindW", CharSet = CharSet.Unicode)]
        public static extern int Find(String AStr,
                                            TFNFindCallback ACallback,
                                            String ADir,
                                            String AExcludeDir,
                                            String AFilter,
                                            int ACount,
                                            int Afrom,
                                            bool ASpaceOr,
                                            bool AWholeWords,
                                            bool ACaseSensitive,
                                            bool AIncludeDir,
                                            bool AIncludeFiles,
                                            UInt16 ATimeoutMS);
        
        static void Main(string[] args)
        {

            if (IntPtr.Size == 4)//32位系统
              Find("*.exe", FindCallback, "", "", "", 1000, 0, true, false, false, false, true, 1000);
            else if(IntPtr.Size == 8)//64位系统
              Find64("*.exe", FindCallback, "", "", "", 1000, 0, true, false, false, false, true, 1000);
        }


        public static String[] getStringArrayFromPPChar(IntPtr buffer,int bufferCount, Encoding  e)
        {
            String[] ret = new String[bufferCount];
            for (int i = 0; i < bufferCount; i++)
            {
                IntPtr cur = Marshal.ReadIntPtr(buffer, IntPtr.Size * i);
                List<byte> b = new List<byte>();
                byte cb = 0;
                byte lb = 0;
                int pos = 0;
                while (true)
                {
                    cb = Marshal.ReadByte(cur, pos);
                    pos++;
                    b.Add(cb);

                    if (e.IsSingleByte)
                    {
                        if(cb == 0)
                            break;
                    }
                    else
                    if ((b.Count % 2) == 0 && cb == 0 && lb == 0)
                    {
                        break;
                    }
                    lb = cb;
                }
                ret[i] = e.GetString(b.ToArray());
            }
            return ret;
        }

        public static void FindCallback(IntPtr buffer, int bufferCount, int totalCount, int ErrorCode)
        {
            Encoding e = Encoding.Unicode;
            String[] filenames = getStringArrayFromPPChar(buffer, bufferCount, e);
            for(int i=0; i< filenames.Length; i++){
                Console.WriteLine(filenames[i]);
            }
        }
    }


}
