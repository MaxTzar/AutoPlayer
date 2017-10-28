- la classe BackgroundImage renvoie true si la sample image est à la position (i,j) dans la background image.
attention, i et j sont ici respectivement la ligne et la colonne.

- la classe KeyboardCapture est faite pour capturer les évènements clavier indépendamment de la fenêtre sélectionnée.
pour l'utiliser, par exemple:

QObject::connect(KeyboardCapture::instance(), SIGNAL(keyPressed(uint)), this, SLOT(onKeyPressed(uint)));

void MainWindow::onKeyPressed(uint key)
{
    if (key == VK_F12)
    {
        // ...
    }
}

- la classe mouse simule des déplacements (via QCursor::setPos) et clics souris (via l'API Windows)
tu peux commenter les parties boost pour éviter d'avoir à configurer le projet.
sinon il faut rajouter qqch comme ça dans le .pro:

BOOST_INSTALL = $${PWD}/../../utils/boost_1_60_0
INCLUDEPATH += $${BOOST_INSTALL}

- la classe Screenshot permet de renvoyer un screenshot de tout l'écran sous forme de QImage.
En réalité Qt fait tout le boulot ;-) Il faut juste utiliser grabWindow() de la classe QScreen.

voili voilou, have fun!