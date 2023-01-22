struct book {
    char title[100];
    char author[100];
    int year;
};

#define NUMBER_OF_BOOKS 30

struct book books[NUMBER_OF_BOOKS] = {
        {"The Lord of the Rings",                     "J.R.R. Tolkien", 1954},
        {"The Hobbit",                                "J.R.R. Tolkien", 1937},
        {"The Silmarillion",                          "J.R.R. Tolkien", 1977},
        {"The Hitchhiker's Guide to the Galaxy",      "Douglas Adams",  1979},
        {"The Restaurant at the End of the Universe", "Douglas Adams",  1980},
        {"Life, the Universe and Everything",         "Douglas Adams",  1982},
        {"So Long, and Thanks for All the Fish",      "Douglas Adams",  1984},
        {"Mostly Harmless",                           "Douglas Adams",  1992},
        {"The Hitchhiker's Guide to the Galaxy",      "Douglas Adams",  2005},
        {"The Hitchhiker's Guide to the Galaxy",      "Douglas Adams",  2009},
        {"The Republic",                              "Plato",          380},
        {"The Phaedo",                                "Plato",          360},
        {"The Phaedrus",                              "Plato",          360},
        {"The Symposium",                             "Plato",          360},
        {"The Apology",                               "Plato",          360},
        {"The Crito",                                 "Plato",          360},
        {"The Meno",                                  "Plato",          360},
        {"The Gorgias",                               "Plato",          360},
        {"The Euthyphro",                             "Plato",          360},
        {"The Euthydemus",                            "Plato",          360},
        {"The Laches",                                "Plato",          360},
        {"The Charmides",                             "Plato",          360},
        {"The Lysis",                                 "Plato",          360},
        {"The Hippias Major",                         "Plato",          360},
        {"The Hippias Minor",                         "Plato",          360},
        {"The Ion",                                   "Plato",          360},
        {"The Menexenus",                             "Plato",          360},
        {"The Statesman",                             "Plato",          360},
        {"The Laws",                                  "Plato",          360},
        {"The Symposium",                             "Plato",          360}};