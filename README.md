# DomesProject
1)Το header με το struct χρησιμοποιείται για να μην φτιάχνω σε κάθε κλάση διαφορετικό struct για να βάζω μέσα λέξη-συχνότητα. Οπότε έφτιαξα ένα header που ελπίζω (fingers crossed) να το κάνει include ο Παπαδόπουλος:)
2)Γενικά οι δομές τρέχουν σε καλούς χρόνους (Στο small-file το insert κάνει κάπου στα 2-5 δευτερόλεπτα-φαντάζομαι το ίδιο θα γίνεται και στο searching).
3)Μπορείς να χρησιμοποιήσεις τις δομές που έφτιαξα και να προσθέσεις τις παραπάνω λειτουργίες(φαντάζομαι για το AVL θα είναι 2 πράγματα παραπάνω, δεν χρειάζεται να γράψεις όλη την κλάση από την αρχή).
4)Πρέπει επίσης να αποφασίσουμε αν θα τρέξουμε όλες τις δομές μαζί, ή μία μία (στο small-file όλα μαζί κάνουν 5 δεύτερα insert, αλλά στο μεγάλο το φοβάμαι λίγο)
5)Το insert στο μεγάλο αρχείο στον Αταξινόμητο κάνει πολύ ώρα και δεν το είδα ποτέ να τελειώνει(ΑΛΛΑ ΔΕΝ ΚΡΑΣΑΡΕΙ!1!1), στο δυαδικό δέντρο κάνει 4 λεπτά και στο Hashing πάλι δεν το είδα να τελειώνει-ενώ θεωρητικά θα έπρεπε να τελειώνει πιο γρήγορα από όλα, λόγω μάλλον του realloc κάνει πολύ ώρα.Για search δεν είδα ακόμα χρόνους.
6)Κάθε κλάση έχει σχόλια σχεδόν σε κάθε γραμμή (το οποίο είναι αηδιαστικό, αλλά better save than sorry) οπότε σχεδόν έχει βγει και η έκθεση. Αν χρειαστεί κάτι άλλο πάλι θα το δούμε.

UPDATE
7)Έφτιαξα μια αρκετά τίμια main που τρέχει όλες τις δομές μάζι, καταγράφει read/search χρόνο και γράφει τα αποτελέσματα της σε ένα text file. Το πρόβλημα δημιουργείται όταν ο Παπαδόπουλος θα πρέπει να τρέξει το μεγάλο-gutenberg-αρχείο, στο οποίο ο Αταξινόμητος που είναι πρώτος κάνει ΑΙΩΝΕΣ. Long story short πρέπει να δούμε πως θα τρέξουμε τις δομές μας.
8)Έγιναν μερικές μικροαλλαγές στις δομές γιατί πρόσθεσα μια μέθοδο που γυρνάει την συχνότητα μιας λέξης. 
