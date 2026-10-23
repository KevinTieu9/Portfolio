
namespace GUIChat
{
    partial class Form2
    {
private System.ComponentModel.IContainer components = null;
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
private void InitializeComponent()
        {
            this.ReplyBox = new System.Windows.Forms.TextBox();
            this.CommentBox = new System.Windows.Forms.TextBox();
            this.ConfirmPost = new System.Windows.Forms.Button();
            this.UsersOn = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // ReplyBox
            // 
            this.ReplyBox.Location = new System.Drawing.Point(244, 2);
            this.ReplyBox.Multiline = true;
            this.ReplyBox.Name = "ReplyBox";
            this.ReplyBox.ReadOnly = true;
            this.ReplyBox.Size = new System.Drawing.Size(309, 273);
            this.ReplyBox.TabIndex = 0;
            this.ReplyBox.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // CommentBox
            // 
            this.CommentBox.Location = new System.Drawing.Point(244, 281);
            this.CommentBox.Multiline = true;
            this.CommentBox.Name = "CommentBox";
            this.CommentBox.Size = new System.Drawing.Size(309, 126);
            this.CommentBox.TabIndex = 1;
            this.CommentBox.TextChanged += new System.EventHandler(this.CommentBox_TextChanged);
            // 
            // ConfirmPost
            // 
            this.ConfirmPost.Location = new System.Drawing.Point(131, 281);
            this.ConfirmPost.Name = "ConfirmPost";
            this.ConfirmPost.Size = new System.Drawing.Size(107, 126);
            this.ConfirmPost.TabIndex = 2;
            this.ConfirmPost.Text = "Confirm";
            this.ConfirmPost.UseVisualStyleBackColor = true;
            this.ConfirmPost.Click += new System.EventHandler(this.ConfirmPost_Click);
            // 
            // UsersOn
            // 
            this.UsersOn.Location = new System.Drawing.Point(131, 2);
            this.UsersOn.Multiline = true;
            this.UsersOn.Name = "UsersOn";
            this.UsersOn.ReadOnly = true;
            this.UsersOn.Size = new System.Drawing.Size(107, 273);
            this.UsersOn.TabIndex = 3;
            this.UsersOn.TextChanged += new System.EventHandler(this.UsersOn_TextChanged);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(554, 408);
            this.Controls.Add(this.UsersOn);
            this.Controls.Add(this.ConfirmPost);
            this.Controls.Add(this.CommentBox);
            this.Controls.Add(this.ReplyBox);
            this.Name = "Form2";
            this.Text = "Form2";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox ReplyBox;
        private System.Windows.Forms.TextBox CommentBox;
        private System.Windows.Forms.Button ConfirmPost;
        private System.Windows.Forms.TextBox UsersOn;
    }
}