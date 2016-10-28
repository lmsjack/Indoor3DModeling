using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

namespace SerialCommAndCtrlServoStep
{
    public partial class Form1 : Form
    {
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            sp.Close();
        }

        SerialPort sp;
        int repeatNum = 10;
        int stepunit = 10;
        public Form1()
        {
            InitializeComponent();
            sp = new SerialPort("COM3",38400);
            sp.Open();
        }

        private void start_Click(object sender, EventArgs e)
        {
            string filename = "";
            filename += this.tpx.Text.ToString() + "_";
            filename += this.tpy.Text.ToString() + "_";
            filename += this.tpz.Text.ToString() + "_";
            filename += this.tdx.Text.ToString() + "_";
            filename += this.tdy.Text.ToString() + "_";
            filename += this.tdz.Text.ToString() + ".txt";

            using(var file = new StreamWriter(filename))
            {
                for(int i = 0; i < 1; i++)
                {
                    //Stack<int> depthList = new Stack<int>();
                    bool flag = true;
                    for(int k = 30; k < 180; k += 10)
                    {
                        Stack<int> depthList = new Stack<int>();
                        for (int j = 0; j < repeatNum; j++)
                        {
                            string command = "";
                            if (flag)
                            {
                                command = 1.ToString() + "," + stepunit.ToString() + "," + k.ToString() + "," + "#Trigger," + 1.ToString();
                            }
                            else
                            {
                                command = 1.ToString() + "," + 0.ToString() + "," + k.ToString() + "," + "#Trigger," + 1.ToString();
                            }

                            flag = false;

                            sp.WriteLine(command);
                            string rcvStr = sp.ReadLine();
                            string distValue = "";
                            for(int l = 0; l < rcvStr.Length; l++)
                            {
                                if (rcvStr[l] > 47&&rcvStr[l]<58)
                                {
                                    distValue += rcvStr[l];
                                }
                            }
                            if(distValue!="")
                            {
                                depthList.Push(Convert.ToInt32(distValue));
                            }
                            //file.Write(i.ToString()+" "+k.ToString()+" "+distValue+"\n");
                        }
                        if(depthList.Count!=0)
                        {
                            int dist = depthList.Pop();
                            file.Write(i.ToString() + " " + k.ToString() + " " + dist.ToString() + "\n");
                        }
                    }
                }
            }
        }
    }
}
