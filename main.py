


from fastapi import FastAPI

app = FastAPI()

@app.get("/pedroammes")
def root(nome: str):
    return {"Hello": f"{nome}"}


from build.Debug import myModule

print(myModule.addTwoNumbers(1,2))

aluno1 = myModule.ClassePython("victor", 11)
print(aluno1.name_)
