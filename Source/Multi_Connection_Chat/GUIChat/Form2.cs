/*
 * Form2.cs
 * CS 346 — Multi-Connection Chat
 *
 * Author: Kevin Tieu
 *
 * Main chat window. Shows messages and sends new ones.
 */

using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace GUIChat
{
    public partial class Form2 : Form
    {
        private const int WritePort = 3462;
        private const int ReadPort = 3463;

        private Thread receiveThread;
        private bool keepReceiving;

        /*
         * Form2
         * Build the chat window. Open the receive connection
         * to the server and start showing messages as they arrive.
         * return nothing
         */
        public Form2()
        {
            InitializeComponent();
            UsersOn.Text = Form1.InputName;
            keepReceiving = true;
            receiveThread = new Thread(ReceiveLoop);
            receiveThread.IsBackground = true;
            receiveThread.Start();
        }

        /*
         * textBox1_TextChanged
         * ReplyBox is read-only. Nothing to do when its text changes.
         *
         * sender - the control that raised the event
         * e      - the event arguments
         * return nothing
         */
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
        }

        /*
         * UsersOn_TextChanged
         * UsersOn is read-only. Nothing to do when its text changes.
         *
         * sender - the control that raised the event
         * e      - the event arguments
         * return nothing
         */
        private void UsersOn_TextChanged(object sender, EventArgs e)
        {
        }

        /*
         * CommentBox_TextChanged
         * Enable the post button only when the user has typed something.
         *
         * sender - the control that raised the event
         * e      - the event arguments
         * return nothing
         */
        private void CommentBox_TextChanged(object sender, EventArgs e)
        {
            ConfirmPost.Enabled = CommentBox.Text.Trim().Length > 0;
        }

        /*
         * ConfirmPost_Click
         * Send the comment-box text to the server, then clear the box.
         *
         * sender - the control that raised the event
         * e      - the event arguments
         * return nothing
         */
        private void ConfirmPost_Click(object sender, EventArgs e)
        {
            string message = CommentBox.Text.Trim();
            // Do nothing if the box is empty
            if (message.Length == 0)
            {
                return;
            }

            try
            {
                // Connect to the write port
                using (TcpClient client = new TcpClient(Form1.InputAddress, WritePort))
                using (BufferedStream stream = new BufferedStream(client.GetStream()))
                using (BinaryWriter writer = new BinaryWriter(stream))
                {
                    // Send the access key so the server knows who we are
                    byte[] keyBytes = Encoding.UTF8.GetBytes(Form1.AuthKey);
                    writer.Write(IPAddress.HostToNetworkOrder(keyBytes.Length));
                    writer.Write(keyBytes);

                    byte[] messageBytes = Encoding.UTF8.GetBytes(message);
                    writer.Write(IPAddress.HostToNetworkOrder(messageBytes.Length));
                    writer.Write(messageBytes);
                    stream.Flush();
                }

                CommentBox.Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Could not send message: " + ex.Message,
                                "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /*
         * ReceiveLoop
         * Connect to the read port, send the auth key, and append each
         * incoming message to the reply box. Runs on a background thread.
         * return nothing
         */
        private void ReceiveLoop()
        {
            try
            {
                using (TcpClient client = new TcpClient(Form1.InputAddress, ReadPort))
                using (BufferedStream stream = new BufferedStream(client.GetStream()))
                using (BinaryReader reader = new BinaryReader(stream))
                using (BinaryWriter writer = new BinaryWriter(stream))
                {
                    // Send the access key so the server knows who we are
                    byte[] keyBytes = Encoding.UTF8.GetBytes(Form1.AuthKey);
                    writer.Write(IPAddress.HostToNetworkOrder(keyBytes.Length));
                    writer.Write(keyBytes);
                    stream.Flush();

                    while (keepReceiving)
                    {
                        int nameLength = IPAddress.NetworkToHostOrder(reader.ReadInt32());
                        byte[] nameBytes = reader.ReadBytes(nameLength);
                        string name = Encoding.UTF8.GetString(nameBytes);

                        int messageLength = IPAddress.NetworkToHostOrder(reader.ReadInt32());
                        byte[] messageBytes = reader.ReadBytes(messageLength);
                        string message = Encoding.UTF8.GetString(messageBytes);

                        string line = name + ": " + message + Environment.NewLine;
                        if (ReplyBox.InvokeRequired)
                        {
                            ReplyBox.Invoke(new Action(() => ReplyBox.AppendText(line)));
                        }
                        else
                        {
                            ReplyBox.AppendText(line);
                        }
                    }
                }
            }
            catch (Exception)
            {
                // Connection closed or server stopped. Leave the window open.
            }
        }

        /*
         * OnFormClosing
         * Stop the receive thread when the window closes.
         *
         * e - the close event arguments
         * return nothing
         */
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            keepReceiving = false;
            base.OnFormClosing(e);
        }
    }
}
