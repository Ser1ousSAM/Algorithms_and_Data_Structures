using System;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml;


namespace RegExpLab
{
    class Program
    {
        static void Main(string[] args)
        {
            string str = "wow, it's compiled -_-";
            Console.WriteLine(str);

            string original;
            try
            {
                using (StreamReader sr = new StreamReader("Dictionary.xml"))
                {
                    original = sr.ReadToEnd();
                    Console.WriteLine("len of string file:");
                    Console.WriteLine(original.Length);
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка чтения файла: \"Dictionary.xml\"\n{0}", ex);
                return;
            }

            //Ищет 1 или более идущих подряд символа слова
            //Regex re = new Regex(@"\w+");
            //Слова начинающиеся с цифр и заканчивающиеся символами слова
            //Regex re = new Regex(@"\b[0-9]+\w+\b");
            //Соответствуют любому слову, включающему хотя бы одну цифру
            //Regex re = new Regex(@"\b\w*\d+\w*\b");
            //Слова, заканчивающиеся на 3
            //Regex re = new Regex(@"\w+3\b");
            //Два одинаковых символа подряд
            //Regex re = new Regex(@"(\w)\1");
            //Все слова со сдвоенными символами
            //Regex re = new Regex(@"\w*(\w)\1\w*");
            //Слова только с латинскими буквами и цифрами
            //Regex re = new Regex(@"\b[0-9,a-z]+\b");
            //Слова, имеющие хотя бы одну латинскую букву
            //Regex re = new Regex(@"\b\w*[0-9,a-z]+\w*\b");
            //Все листовые теги
            //Regex re = new Regex(@"<([a-z]+)>\w+</\1>");

            //MatchCollection mc = re.Matches(str);
            //foreach (var m in mc)
            //    Console.WriteLine(m);
            //MatchCollection mc = re.Matches(re.Replace(orig, ""));          

            //Console.WriteLine(re.Replace(orig, ""));

            Regex reg = new Regex(@".....................\s+[.,()!?].....................");
            reg = new Regex(@"\s+[,]");
            string transformed = reg.Replace(original, ",");
            reg = new Regex(@"<article>?:/W*</article>");
            transformed = reg.Replace(transformed, "");

            string path = "Dictionary.xml";
            try
            {
                using (StreamWriter sw = new StreamWriter(path))
                {
                    sw.Write(transformed);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка сохранений в файл: \"{0}\"\n{1}", path, ex);
                return;
            }

            XmlDocument doc = new XmlDocument();
            doc.LoadXml(transformed);

        }
    }
}
