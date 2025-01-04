import clang.cindex
clang.cindex.Config.set_library_file('/opt/homebrew/Cellar/llvm/19.1.4/lib/libclang.dylib')
from flask import Flask, render_template, request
import subprocess
import os
import uuid
import traceback
import tempfile
from analyze_ast import inject_tracers  # Import du script AST



app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def home():
    sorted_numbers = None
    if request.method == 'POST':
        numbers = request.form['numbers']
        algorithm = request.form['algorithm']
        try:
            # Convertir la liste de nombres
            number_list = [int(num.strip()) for num in numbers.split(',')]
            
            # Préparer la commande pour exécuter le fichier compilé
            executable = f"sorting_algorithms/{algorithm}"
            command = [f"./{executable}"] + [str(num) for num in number_list]

            # Exécuter le fichier C et capturer la sortie
            result = subprocess.run(command, capture_output=True, text=True, check=True)
            # Remplacer les sauts de ligne pour le rendu HTML
            sorted_numbers = result.stdout.strip().replace("\n", "<br>")
        except Exception as e:
            sorted_numbers = f"Erreur : {e}"
    return render_template('home.html', sorted_numbers=sorted_numbers)


@app.route('/about', methods=['GET', 'POST'])
def about():
    output = ""
    code = ""
    injected_filename = None
    if request.method == 'POST':
        # Étape 1 : Vérification des entiers
        values = request.form['values']
        try:
            integers = [int(v) for v in values.split(',')]
            if len(integers) != 4:
                output = "Veuillez entrer exactement 4 entiers séparés par des virgules."
                return render_template('about.html', output=output, code=code)
        except ValueError:
            output = "Les valeurs doivent être des entiers séparés par des virgules."
            return render_template('about.html', output=output, code=code)

        # Étape 2 : Vérification du code utilisateur
        code = request.form['code']
        if not code.strip():
            output = "Veuillez entrer une fonction en C avant de soumettre."
            return render_template('about.html', output=output, code=code)

        # Étape 3 : Ajouter automatiquement un `main` temporaire
        full_code = f"""
#include <stdio.h>
#include <stdlib.h>

// Code utilisateur
{code}

// Fonction `main` temporaire
int main() {{
    int tab[] = {{{', '.join(map(str, integers))}}};
    int n = sizeof(tab) / sizeof(tab[0]);

    printf("Tableau initial : ");
    for (int i = 0; i < n; i++) {{
        printf("%d ", tab[i]);
    }}
    printf("\\n");

    tri_a_bulle(tab, n);  // Appeler la fonction utilisateur

    printf("Tableau final : ");
    for (int i = 0; i < n; i++) {{
        printf("%d ", tab[i]);
    }}
    printf("\\n");

    return 0;
}}
        """

        temp_filename = "temp_code.c"
        try:
            # Sauvegarder le code utilisateur dans un fichier temporaire
            with open(temp_filename, "w") as temp_file:
                temp_file.write(full_code)

            # Injecter des affichages pour chaque modification significative
            injected_filename = inject_tracers(temp_filename)

            # Compiler le code modifié
            compile_command = ['gcc', injected_filename, '-o', 'temp_code.out']
            process_compile = subprocess.run(compile_command, capture_output=True, text=True)

            if process_compile.returncode == 0:
                # Exécuter le programme compilé pour récupérer les résultats
                process_run = subprocess.run(['./temp_code.out'], capture_output=True, text=True)
                if process_run.returncode == 0:
                    output = process_run.stdout
                else:
                    output = f"Erreur à l'exécution : {process_run.stderr}"
            else:
                output = f"Erreur de compilation :\n{process_compile.stderr}"
        except Exception as e:
            output = f"Une erreur est survenue : {str(e)}"
        finally:
            # Nettoyer les fichiers temporaires
            if os.path.exists(temp_filename):
                os.remove(temp_filename)
            if os.path.exists('temp_code.out'):
                os.remove('temp_code.out')
            if injected_filename and os.path.exists(injected_filename):
                os.remove(injected_filename)

    return render_template('about.html', output=output, code=code)

if __name__ == '__main__':
    app.run(debug=True)
