using System;
using System.Windows.Forms;

namespace SolveEquation
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void OnTextChanged(object sender, EventArgs e)
        {
            double[] z = new double[10];
            double.TryParse(txtR0.Text, out z[0]);
            double.TryParse(txtI0.Text, out z[1]);
            double.TryParse(txtR1.Text, out z[2]);
            double.TryParse(txtI1.Text, out z[3]);
            double.TryParse(txtR2.Text, out z[4]);
            double.TryParse(txtI2.Text, out z[5]);
            double.TryParse(txtR3.Text, out z[6]);
            double.TryParse(txtI3.Text, out z[7]);
            double.TryParse(txtR4.Text, out z[8]);
            double.TryParse(txtI4.Text, out z[9]);
#if false
            double[] x = SolveEquationNET.Equation.Solve(z);
#else
            double[] x = Solve.SolveEquation(z);
#endif
            int n = 0;
            if (x != null)
            {
                n   =   x.Length / 3;
            }
            const double d = 1e-10;
            if (n >= 1)
            {
                txtRA.Text = x[0].ToString();
                txtIA.Text = x[1].ToString();
                lblA.Text = x[2].ToString("0.e+000");
                lblA.ForeColor = Math.Abs(x[2]) > d ? System.Drawing.Color.Red : System.Drawing.Color.Blue;
            }
            else
            {
                lblA.Text = ""; txtRA.Text = ""; txtIA.Text = "";
            }
            if (n >= 2)
            {
                txtRB.Text = x[3].ToString();
                txtIB.Text = x[4].ToString();
                lblB.Text = x[5].ToString("0.e+000");
                lblB.ForeColor = Math.Abs(x[5]) > d ? System.Drawing.Color.Red : System.Drawing.Color.Blue;
            }
            else
            {
                lblB.Text = ""; txtRB.Text = ""; txtIB.Text = "";
            }
            if (n >= 3)
            {
                txtRC.Text = x[6].ToString();
                txtIC.Text = x[7].ToString();
                lblC.Text = x[8].ToString("0.e+000");
                lblC.ForeColor = Math.Abs(x[8]) > d ? System.Drawing.Color.Red : System.Drawing.Color.Blue;
            }
            else
            {
                lblC.Text = ""; txtRC.Text = ""; txtIC.Text = "";
            }
            if (n >= 4)
            {
                txtRD.Text = x[9].ToString();
                txtID.Text = x[10].ToString();
                lblD.Text = x[11].ToString("0.e+000");
                lblD.ForeColor = Math.Abs(x[11]) > d ? System.Drawing.Color.Red : System.Drawing.Color.Blue;
            }
            else
            {
                lblD.Text = ""; txtRD.Text = ""; txtID.Text = "";
            }
        }
    }
}
