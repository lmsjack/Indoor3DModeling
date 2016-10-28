using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Numerics;

namespace test
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Vector3> vectorList = new List<Vector3>();
            List<Vector2> degreeList = new List<Vector2>();
            degreeList.Add(new Vector2(140, 109));
            degreeList.Add(new Vector2(130, 95));
            degreeList.Add(new Vector2(120, 99));
            degreeList.Add(new Vector2(110, 89));
            degreeList.Add(new Vector2(100, 84));
            degreeList.Add(new Vector2(90, 82));
            degreeList.Add(new Vector2(80, 81));
            degreeList.Add(new Vector2(70, 82));
            degreeList.Add(new Vector2(60, 100));
            degreeList.Add(new Vector2(50, 118));
            degreeList.Add(new Vector2(40, 122));
            degreeList.Add(new Vector2(30, 139));
            degreeList.Add(new Vector2(20, 76));
            degreeList.Add(new Vector2(10, 31));
            degreeList.Add(new Vector2(0, 30));
            for(float i = 0; i < (float)Math.PI * 2; i += (float)Math.PI / 80)
            {
                for(int j = 1; j < 15; j++)
                {
                    vectorList.Add(new Vector3(degreeList[j].Y * (float)Math.Sin((degreeList[j].X)*Math.PI/180) * (float)Math.Cos(i), 
                                                degreeList[j].Y * (float)Math.Sin((degreeList[j].X) * Math.PI / 180) * (float)Math.Sin(i),
                                                degreeList[j].Y * (float)Math.Cos((degreeList[j].X) * Math.PI / 180)));
                    vectorList.Add(new Vector3(degreeList[j-1].Y * (float)Math.Sin(degreeList[j-1].X) * (float)Math.Cos(i),
                                                degreeList[j - 1].Y * (float)Math.Sin((degreeList[j - 1].X) * Math.PI / 180) * (float)Math.Sin(i), 
                                                degreeList[j - 1].Y * (float)Math.Cos((degreeList[j - 1].X) * Math.PI / 180)));
                    vectorList.Add(new Vector3(degreeList[j - 1].Y * (float)Math.Sin((degreeList[j - 1].X) * Math.PI / 180) * (float)Math.Cos(i+ (float)Math.PI / 80),
                                                degreeList[j - 1].Y * (float)Math.Sin((degreeList[j - 1].X) * Math.PI / 180) * (float)Math.Sin(i + (float)Math.PI / 80), 
                                                degreeList[j - 1].Y * (float)Math.Cos((degreeList[j-1].X) * Math.PI / 180)));
                    vectorList.Add(new Vector3(degreeList[j].Y * (float)Math.Sin((degreeList[j].X) * Math.PI / 180) * (float)Math.Cos(i + (float)Math.PI / 80),
                                                degreeList[j].Y * (float)Math.Sin((degreeList[j].X) * Math.PI / 180) * (float)Math.Sin(i + (float)Math.PI / 80), 
                                                degreeList[j].Y * (float)Math.Cos((degreeList[j].X) * Math.PI / 180)));
                }
                
            }
            using (var file = new StreamWriter("test.obj"))
            {
                //foreach (var vec in vectorList)
                //{
                //    file.Write("v " + vec.X.ToString() + " " + vec.Y.ToString() + " " + vec.Z.ToString() + "\n");
                //}

                for(int i = 0; i < vectorList.Count; i++)
                {
                    file.Write("v " + vectorList[i].X.ToString() + " " + vectorList[i].Y.ToString() + " " + vectorList[i].Z.ToString() + "\n");
                }

                for(int i=0;i<vectorList.Count/4;i++)
                {
                    file.Write("f " + (4*i + 1).ToString() + " " + (4 * i + 2).ToString() + " " + (4 * i + 3).ToString() + " " + (4 * i + 4).ToString() + "\n");
                }
            }
        }
    }
}
