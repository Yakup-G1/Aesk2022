using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;

namespace Telemetry
{
    /*
     * openChildForm fonkisyonu açılacak olan formu ve formun açılacağı paneli parametre olarak alır
     * kullanmak için gerekli yerde fonksiyonun içine bu parametreleri giriniz
     * anasayfaya dönmek için ise activeForm değişkeni kullanılmıştır
     * anasayfaya dönme bölümünde activeForm'un null olup olmadığını kontrol edin
    */

    //BURAYA YAZICAN
    public partial class FormManagement : Form
    {
        public static Form oldForm;
        public static void openChildForm(Form childForm, Panel panelChildForm)
        {
            if (oldForm != null)
                oldForm.Hide();

            childForm.TopLevel = false;
            childForm.TopMost = true;
            childForm.FormBorderStyle = FormBorderStyle.None;
            childForm.Dock = DockStyle.Fill;
            panelChildForm.Controls.Add(childForm); //bak
            panelChildForm.Tag = childForm;
            childForm.BringToFront();
            childForm.Show();

            oldForm = childForm;
        }
    }
}
