/*
 * Form2.cs
 * CS 346 — Multi-Connection Chat
 *
 * Author: Kevin Tieu
 *
 * Main chat window. Shows messages and sends new ones.
 */
﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUIChat
{
    public partial class Form2 : Form
    {
        /*
         * Form2
         * Build the chat window. Open the send and receive connections
         * to the server and start showing messages as they arrive.
         */
        public Form2()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void UsersOn_TextChanged(object sender, EventArgs e)
        {

        }

        private void CommentBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void ConfirmPost_Click(object sender, EventArgs e)
        {

        }
    }
}
