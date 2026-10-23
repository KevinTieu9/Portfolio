/*
 * Program.cs
 * CS 346 — Multi-Connection Chat
 *
 * Author: Kevin Tieu
 *
 * Starts the Windows Forms client.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Text;

namespace GUIChat
{
    static class Program
    {

        //private static String mAddress = "";
[STAThread]
        /*
         * Main
         * Start the Windows Forms client and open the login form.
         *
         * return nothing
         */
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

        }
    }
}
