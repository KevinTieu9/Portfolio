/*
 * ConsoleLogger.cs
 * CS 346 — Multi-Connection Chat
 *
 * Author: Kevin Tieu
 *
 * Writes log messages to the console.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace ChatServer.Library.Logging
{
    public class ConsoleLogger : ILogger
    {
        public void Log(string message)
        {
            Console.WriteLine(message);
        }

        public void Log(string message, params object[] args)
        {
            Console.WriteLine(message, args);
        }

        public void Log(string message, LogPriority severity)
        {
            Log(message);
        }
        public void Log(LogPriority severity, string message, params object[] args)
        {
            Log(message, args);
        }

    }
}
