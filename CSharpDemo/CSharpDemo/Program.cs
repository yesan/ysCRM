using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CSharpDemo
{
    class Program
    {

        public delegate void TFNFindCallback(IntPtr buffer, int bufferCount, int totalCount, int ErrorCode);

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
//        const AStr: PChar;	搜索关键词
//ACallback: TResultCallBack;	回调函数
//const ADir: PChar;	制定目录（单个）
//const AFilter: PChar;	后缀过滤（多个）
//const ACount: Integer = 100;	返回结果数量
//const Afrom: Integer = 0;	开始结果位置
//const ASpaceOr: Boolean = False;	是否匹配任一关键词
//const AWholeWords: Boolean = False;	匹配全词
//const ACaseSensitive: Boolean = False;	区分大小写
//const AIncludeDir: Boolean = True;	搜索目录
//const AIncludeFiles: Boolean = True;	搜索文件
//const ATimeoutMS: Word = 1000	超时时间

        static void Main(string[] args)
        {

            if (IntPtr.Size == 4)//32位系统
                Find("Test", FindCallback, "", "", "", 100, 0, true, false, false, false, true, 1000);
        }


        public static String[] getStringArrayFromPPChar(IntPtr buffer, int bufferCount, Encoding e)
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
                        if (cb == 0)
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

        //public List<String> list = new List<String>();
        //public String a;
        public static void FindCallback(IntPtr buffer, int bufferCount, int totalCount, int ErrorCode)
        {
            Encoding e = Encoding.Unicode;
            String[] filenames = getStringArrayFromPPChar(buffer, bufferCount, e);
            for (int i = 0; i < filenames.Length; i++)
            {
                Console.WriteLine(filenames[i]);
                //list.Add(filenames[i]);
                //a += filenames[i];
            }
            Console.ReadLine();
        }
    }


}
