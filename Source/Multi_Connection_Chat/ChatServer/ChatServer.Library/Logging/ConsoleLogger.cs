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
        /*
         * Log
         * Write a message to the console.
         *
         * message - the text to write
         * return nothing
         */
        public void Log(string message)
        {
            Console.WriteLine(message);
        }

        /*
         * Log
         * Write a formatted message to the console.
         *
         * message - the format string
         * args    - values to fill into the format string
         * return nothing
         */
        public void Log(string message, params object[] args)
        {
            Console.WriteLine(message, args);
        }

        /*
         * Log
         * Write a message with a severity level to the console.
         *
         * message  - the text to write
         * severity - how important the message is
         * return nothing
         */
        public void Log(string message, LogPriority severity)
        {
            Log(message);
        }
        /*
         * Log
         * Write a formatted message with a severity level to the console.
         *
         * severity - how important the message is
         * message  - the format string
         * args     - values to fill into the format string
         * return nothing
         */
        public void Log(LogPriority severity, string message, params object[] args)
        {
            Log(message, args);
        }

    }
}
