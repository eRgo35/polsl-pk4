# NLP Platform

NLP Platform providing translation and sentiment analysis.

## Authors:
 - Michał Czyż (eRgo35)
 - Dawid Głąb (dawidokox1)

## Instructions

To start a part of software use below Instructions with quick start copy-paste cmds.

### Webserver (Next.js & React)

Make sure to have `nodejs` and `npm` installed.

To install dependecies:

```sh 
npm install
```

To run project use:

```sh
npm run dev
```

To build and run on production:

```sh
npm run build && npm run start
```

### API Middleware (Python)

Make sure you have `python` installed.

```sh
cd api
```

Use activate.sh to prepare all dependecies:

```sh
./activate.sh
```

Activate venv:

```sh
source ./.venv/bin/activate
```

To run:

```sh 
python main.py
```

To leave path

```sh
deactivate
```

### Core Platform (C++)

Make sure you have installed `base-devel`, `boost`, and `cppzmq`.

To compile C++ just run:

```sh 
cd nlp
```

```sh
mold -run make
```

To style all files use:
```sh
clang-format -i -style=Google **/*.cpp **/*.hpp
```

### Documentation (LaTeX)

Make sure you have `texlive` installed and all its required dependecies

To compile tex file into a pdf use:
```sh
cd docs
```

```sh 
pdflatex <file_name>.tex
```
