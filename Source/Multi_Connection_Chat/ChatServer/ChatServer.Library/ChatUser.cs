/*
 * ChatUser.cs
 * CS 346 — Multi-Connection Chat
 *
 * Author: Kevin Tieu
 *
 * Represents one connected user and their network streams.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace ChatServer.Library
{
    public class ChatUser
    {
        public string Name { get; set; }
        public string Address { get; set; }
        public string AuthString { get; set; }
    }
}
