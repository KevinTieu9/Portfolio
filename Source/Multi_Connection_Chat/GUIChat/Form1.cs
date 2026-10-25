/*
 * Form1.cs
 * CS 346 — Multi-Connection Chat
 *
 * Author: Kevin Tieu
 *
 * Login form. Collects the username and password and connects to the server.
 */

using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace GUIChat
{
public partial class Form1 : Form
    {
        private const int AuthPort = 3461;
        private const int WritePort = 3462;
        private const int ReadPort = 3463;

        private static string authKey = "";
        private static ArrayList messages = new ArrayList();

        public static string InputAddress = "";
        public static string InputName = "";
        public static string InputPass = "";

        /*
         * Form1
         * Build the login form. The address, username, and password boxes
         * are filled in by the designer. This method only starts the form.
         */
        public Form1()
        {
            InitializeComponent();
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        public void HelloButton_Click(object sender, EventArgs e)
        {
            InputAddress = AddressText.Text;
            InputName = NameText.Text;
            InputPass = PasswordText.Text;

            try
            {
                using (TcpClient client = new TcpClient(InputAddress, AuthPort))
                using (BufferedStream stream = new BufferedStream(client.GetStream()))
                using (BinaryReader reader = new BinaryReader(stream))
                using (BinaryWriter writer = new BinaryWriter(stream))
                {
                    // Send username length + bytes
                    writer.Write(IPAddress.HostToNetworkOrder(InputName.Length));
                    writer.Write(Encoding.UTF8.GetBytes(InputName));

                    // Send password length + bytes
                    writer.Write(IPAddress.HostToNetworkOrder(InputPass.Length));
                    writer.Write(Encoding.UTF8.GetBytes(InputPass));

                    // Receive auth token
                    int authLength = IPAddress.NetworkToHostOrder(reader.ReadInt32());
                    byte[] authBytes = reader.ReadBytes(authLength);
                    authKey = Encoding.UTF8.GetString(authBytes);
                }

                // Authentication succeeded; open chat form
                this.Hide();
                Form2 chatForm = new Form2();
                chatForm.Show();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Connection or authentication failed: " + ex.Message,
                                "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
