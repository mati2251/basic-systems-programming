struct book {
  long mtype;
  char title[100];
  char author[100];
  int year;
  int index;
};

#define NUMBER_OF_BOOKS 30

struct book books[NUMBER_OF_BOOKS] = {
    {0, "The Lord of the Rings", "J.R.R. Tolkien", 1954, 0},
    {0, "The Hobbit", "J.R.R. Tolkien", 1937, 0},
    {0, "The Silmarillion", "J.R.R. Tolkien", 1977, 0},
    {0, "The Hitchhiker's Guide to the Galaxy", "Douglas Adams", 1979, 0},
    {0, "The Restaurant at the End of the Universe", "Douglas Adams", 1980, 0},
    {0, "Life, the Universe and Everything", "Douglas Adams", 1982, 0},
    {0, "So Long, and Thanks for All the Fish", "Douglas Adams", 1984, 0},
    {0, "Mostly Harmless", "Douglas Adams", 1992, 0},
    {0, "The Hitchhiker's Guide to the Galaxy", "Douglas Adams", 2005, 0},
    {0, "The Hitchhiker's Guide to the Galaxy", "Douglas Adams", 2009, 0},
    {0, "The Republic", "Plato", 380, 0},
    {0, "The Phaedo", "Plato", 360, 0},
    {0, "The Phaedrus", "Plato", 360, 0},
    {0, "The Symposium", "Plato", 360, 0},
    {0, "The Apology", "Plato", 360, 0},
    {0, "The Crito", "Plato", 360, 0},
    {0, "The Meno", "Plato", 360, 0},
    {0, "The Gorgias", "Plato", 360, 0},
    {0, "The Euthyphro", "Plato", 360, 0},
    {0, "The Euthydemus", "Plato", 360, 0},
    {0, "The Laches", "Plato", 360, 0},
    {0, "The Charmides", "Plato", 360, 0},
    {0, "The Lysis", "Plato", 360, 0},
    {0, "The Hippias Major", "Plato", 360, 0},
    {0, "The Hippias Minor", "Plato", 360, 0},
    {0, "The Ion", "Plato", 360, 0},
    {0, "The Menexenus", "Plato", 360, 0},
    {0, "The Statesman", "Plato", 360, 0},
    {0, "The Laws", "Plato", 360, 0},
    {0, "The Symposium", "Plato", 360, 0}};