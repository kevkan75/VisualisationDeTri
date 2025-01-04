import clang.cindex
import re

def inject_tracers(filename, array_name="tab"):
    """
    Injecte des printf après chaque échange significatif dans le tableau
    pour afficher son état complet à chaque étape.
    """
    with open(filename, "r") as f:
        lines = f.readlines()

    modified_lines = []
    for line in lines:
        modified_lines.append(line)
        # Identifier les échanges dans le tableau (tab[i] = ...)
        if f"{array_name}[" in line and "=" in line and ";" in line and "temp" in line:
            # Injecter un affichage après chaque échange significatif
            printf_code = (
                f'    printf(""); '
                f'for (int k = 0; k < sizeof({array_name}) / sizeof({array_name}[0]); k++) printf("%d ", {array_name}[k]); '
                f'printf("\\n");\n'
            )
            modified_lines.append(printf_code)

    # Sauvegarder le fichier injecté
    injected_filename = "temp_injected_code.c"
    with open(injected_filename, "w") as f:
        f.writelines(modified_lines)

    return injected_filename