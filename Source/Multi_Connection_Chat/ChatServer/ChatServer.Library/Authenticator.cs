/*
 * Authenticator.cs
 * CS 346 — Multi-Connection Chat
 *
 * Author: Kevin Tieu
 *
 * Listens for new clients, checks the username and password, and registers them.
 */

using ChatServer.Library.Logging;
using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;

namespace ChatServer.Library
{
    public class Authenticator
    {
        public int ListenPort { get; set; }
        public bool IsRunning { get; private set; }
        public ILogger Logger { get; set; }
        public Server Server { get; set; }

        /*
         * Authenticator
         * Create the authenticator. The listen port and server
         * are set by the caller before Run is called.
         * return nothing
         */
        public Authenticator()
        {
        }

        /*
         * Run
         * Listen on the authentication port. For each new client, read the
         * username and password, check them, and add the user to the active list.
         * Keep doing this until the server is stopped.
         * return nothing
         */
        public void Run()
        {
            IsRunning = true;
            TcpListener listener = new TcpListener(IPAddress.Any, ListenPort);
            listener.Start();
            while (IsRunning)
            {
                Logger.Log("Authenticator waiting for connection on port {0}...", ListenPort);
                TcpClient client = null;
                try
                {
                    client = listener.AcceptTcpClient();

#if DEBUG == false
                    //timeouts affect debugging when stepping through code
                    client.ReceiveTimeout = 5000;
#endif

                }
                catch (Exception ex)
                {
                    Logger.Log("Could not accept TCP client: {0}", ex.Message);
                    continue;
                }
                Logger.Log("Authenticator accepting client: {0}", client.Client.RemoteEndPoint);

                BinaryReader reader = null;
                BinaryWriter writer = null;
                try
                {
                    BufferedStream stream = new BufferedStream(client.GetStream());
                    reader = new BinaryReader(stream);
                    writer = new BinaryWriter(stream);
                    int userNameLength = IPAddress.NetworkToHostOrder(reader.ReadInt32());
                    byte[] userNameBytes = reader.ReadBytes(userNameLength);
                    string userName = Encoding.UTF8.GetString(userNameBytes);

                    int passwordLength = IPAddress.NetworkToHostOrder(reader.ReadInt32());
                    byte[] passwordBytes = reader.ReadBytes(passwordLength);
                    string password = Encoding.UTF8.GetString(passwordBytes);

                    //TODO validate
                    string address = ((IPEndPoint)client.Client.RemoteEndPoint).Address.ToString();
                    ChatUser user = new ChatUser() {
                        Address = address,
                        AuthString = GenerateAccessKey(),
                        Name = userName
                    };
                    Server.ActiveUsers[user.AuthString] = user;
                    writer.Write(IPAddress.HostToNetworkOrder(user.AuthString.Length));
                    writer.Write(Encoding.UTF8.GetBytes(user.AuthString));

                }
                catch (Exception ex)
                {
                    Logger.Log("Authenticator exception handling client {0}, {1}: ", client.Client.RemoteEndPoint, ex.Message);
                }
                finally
                {
                    Logger.Log("Authenticator done handling client {0}", client.Client.RemoteEndPoint);
                    reader.Close();
                    writer.Close();
                    if (client != null)
                    {
                        client.Close();
                    }
                }
            }
        }

        /*
         * GenerateAccessKey
         * Build a random access key for a newly authenticated user.
         *
         * return the key as a string
         */
        public static string GenerateAccessKey()
        {
            var key = new byte[32];
            using (var generator = RandomNumberGenerator.Create())
            {
                generator.GetBytes(key);
            }
            return Convert.ToBase64String(key);
        }
    }
}
