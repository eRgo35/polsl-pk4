"use client";
import * as React from "react";
import {
  Button,
  Container,
  Grid,
  InputAdornment,
  LinearProgress,
  Paper,
  TextField,
  Typography,
} from "@mui/material";
import TranslateIcon from "@mui/icons-material/Translate";
import { baseUrl } from "../lib/backend";
import SaveIcon from "@mui/icons-material/Save";
import { CopyAll } from "@mui/icons-material";

export default function TranslateForm() {
  const models = [
    {
      value: "ct2",
      label: "cTranslate2",
      srcLangs: [
        { code: "auto", name: "Auto Detect" },
      ],
      dstLangs: [
        { code: "en", name: "English" },
        { code: "es", name: "Spanish" },
        { code: "fr", name: "French" },
        { code: "it", name: "Italian" },
        { code: "de", name: "German" },
        { code: "pl", name: "Polish" },
        { code: "ja", name: "Japanese" },
      ],
    },
    {
      value: "mt5",
      label: "Google MT5",
      srcLangs: [
        { code: "en", name: "English" },
        { code: "pl", name: "Polish" },
      ],
      dstLangs: [
        { code: "pl", name: "Polish" },
        { code: "en", name: "English" },
      ],
    },
    {
      value: "opus",
      label: "Opus MT",
      srcLangs: [
        { code: "en", name: "English" },
        { code: "pl", name: "Polish" },
      ],
      dstLangs: [
        { code: "pl", name: "Polish" },
        { code: "en", name: "English" },
      ],
    },
    {
      value: "smt",
      label: "Statistical Machine Translation",
      srcLangs: [
        { code: "en", name: "English" },
      ],
      dstLangs: [
        { code: "pl", name: "Polish" },
      ],
    },
  ];

  const [sourceLanguage, setSourceLanguage] = React.useState(models[0].srcLangs[0].code);
  const [targetLanguage, setTargetLanguage] = React.useState(models[0].dstLangs[0].code);
  const [model, setModel] = React.useState(models[0].value);
  const [inputText, setInputText] = React.useState("");
  const [translation, setTranslation] = React.useState(null);
  const [isLoading, setIsLoading] = React.useState(false);

  const handleTranslate = async () => {
    setIsLoading(true);

    try {
      console.log(JSON.stringify({
        srcLanguage: sourceLanguage,
        dstLanguage: targetLanguage,
        mode: model,
        data: inputText,
      }))
      await fetch(`${baseUrl}/api/translate`, {
        method: "POST",
        headers: {
          Accept: "application/json",
          "Content-Type": "application/json",
          Authorization: "17e1c9878d714c7f83209cc4084ea632",
        },
        body: JSON.stringify({
          srcLanguage: sourceLanguage,
          dstLanguage: targetLanguage,
          mode: model,
          data: inputText,
        }),
      })
        .then((res) => res.json())
        .then(({ data }) => {
          console.log(data);
          setTranslation(data);
        });
    } catch (err) {
      console.error(err);
      setTranslation("An error occoured!");
    }

    setIsLoading(false);
  };

  const handleExport = () => {
    const data =
      "data:text/json;charset=utf-8," +
      encodeURIComponent(JSON.stringify(translation));
    const date = new Date();
    const exportTitle = `translation-${date.getFullYear()}-${
      date.getMonth() + 1
    }-${date.getDate()}-${date.getHours()}-${date.getMinutes()}-${date.getSeconds()}.json`;
    const download = document.createElement("a");
    download.setAttribute("href", data);
    download.setAttribute("download", exportTitle);
    document.body.appendChild(download);
    download.click();
    download.remove();
  };

  const handleCopy = () => {
    return navigator.clipboard.writeText(translation).then(
      function () {
        console.log("Copied to clipboard successfully!");
      },
      function (err) {
        console.error("Failed to copy to clipboard: ", err);
      }
    );
  };

  return (
    <Paper sx={{ padding: 3 }}>
      <h1>Machine Translation Tool!</h1>
      <p>Translate text from one language to other!</p>
      <p>Select a model from a list and choose a language pair</p>
      <Grid container spacing={2}>
        <Grid item xs={6}>
          <TextField
            label="Source Language"
            select
            value={sourceLanguage}
            onChange={(event) => {
              const selectedLangCode = event.target.value;
              const foundModel = models.find((m) => m.value === model);
              console.log(foundModel)
              const selectedLang = foundModel.dstLangs.find((lang) => lang.code === selectedLangCode);
              console.log(selectedLang)
              setSourceLanguage(selectedLang.code);
            }}
            SelectProps={{ native: true }}
          >
            {models.find((m) => m.value === model).srcLangs.map((option) => (
              <option key={option.code} value={option.code}>
                {option.name}
              </option>
            ))}
          </TextField>
        </Grid>
        <Grid item xs={6}>
          <TextField
            label="Target Language"
            select
            value={targetLanguage}
            onChange={(event) => {
              const selectedLangCode = event.target.value;
              const foundModel = models.find((m) => m.value === model);
              console.log(foundModel)
              const selectedLang = foundModel.dstLangs.find((lang) => lang.code === selectedLangCode);
              console.log(selectedLang)
              setTargetLanguage(selectedLang.code);
            }}
            SelectProps={{ native: true }}
          >
            {models.find((m) => m.value === model).dstLangs.map((option) => (
              <option key={option.code} value={option.code}>
                {option.name}
              </option>
            ))}
          </TextField>
        </Grid>
        <Grid item xs={6}>
          <TextField
            label="Model"
            select
            value={model.value}
            onChange={(event) => {
              const selectedModel = event.target.value;
              console.log(selectedModel)
              const foundModel = models.find((model) => model.value === selectedModel)
              console.log(foundModel)
              setSourceLanguage(foundModel.srcLangs[0].code)
              setTargetLanguage(foundModel.dstLangs[0].code)
              setModel(foundModel.value)
            }}
            SelectProps={{ native: true }}
          >
            {models.map((option) => (
              <option key={option.value} value={option.value}>
                {option.label}
              </option>
            ))}
          </TextField>
        </Grid>
        <Grid item xs={12}>
          <TextField
            label="Enter Text to Translate"
            multiline
            minRows={4}
            fullWidth
            value={inputText}
            onChange={(e) => setInputText(e.target.value)}
            InputProps={{
              endAdornment: (
                <InputAdornment position="end">
                  <Button
                    variant="contained"
                    size="small"
                    endIcon={<TranslateIcon />}
                    onClick={handleTranslate}
                  >
                    Translate
                  </Button>
                </InputAdornment>
              ),
            }}
          />
          {translation !== null && (
            <Grid container justifyContent="center" sx={{ mt: 2 }}>
              <TextField
                label="Translated Text"
                multiline
                minRows={4}
                fullWidth
                sx={{ mb: 2 }}
                value={translation}
                disabled={isLoading}
                InputProps={{
                  endAdornment: (
                    <InputAdornment position="end">
                      <Button
                        variant="contained"
                        size="small"
                        endIcon={<CopyAll />}
                        onClick={handleCopy}
                      >
                        Copy
                      </Button>
                    </InputAdornment>
                  ),
                }}
              />
              <Grid container justifyContent="end">
                <Grid item>
                  <Button
                    variant="outlined"
                    onClick={handleExport}
                    startIcon={<SaveIcon />}
                  >
                    Export to JSON
                  </Button>
                </Grid>
              </Grid>
            </Grid>
          )}
          {isLoading ? <LinearProgress sx={{ mt: 2 }} /> : ""}
        </Grid>
      </Grid>
    </Paper>
  );
}
