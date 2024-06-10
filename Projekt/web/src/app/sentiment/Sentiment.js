'use client'
import * as React from 'react';
import { SentimentVeryDissatisfied, SentimentVerySatisfied } from "@mui/icons-material";
import { Button, Grid, InputAdornment, LinearProgress, Paper, TextField, Typography } from "@mui/material";
import { baseUrl } from '../lib/backend';
import SaveIcon from '@mui/icons-material/Save';

export default function SentimentForm() {
  const models = [
    { value: "nltk", label: "NLTK" },
    { value: "pipeline", label: "DistilBERT" },
  ];

  const [model, setModel] = React.useState(models[0].value);
  const [inputText, setInputText] = React.useState("");
  const [analysis, setAnalysis] = React.useState(null);
  const [score, setScore] = React.useState(null);
  const [isLoading, setIsLoading] = React.useState(false);

  const handleAnalyze = async () => {
    setIsLoading(true);

    try {
      await fetch(`${baseUrl}/api/sentiment`, {
        method: 'POST',
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json',
          'Authorization': '17e1c9878d714c7f83209cc4084ea632'
        },
        body: JSON.stringify({
          mode: model,
          data: inputText
        })
      })
        .then(res => res.json())
        .then(({ sentiment, probability }) => {
          console.log(sentiment, probability)
          setAnalysis(sentiment)
          setScore(probability)
        })
    } catch (err) {
      console.error(err);
      setAnalysis("An error occoured!");
    }

    setIsLoading(false);
  };

  const handleExport = () => {
    const data = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(analysis))
    const date = new Date()
    const exportTitle = `analysis-${date.getFullYear()}-${date.getMonth() + 1}-${date.getDate()}-${date.getHours()}-${date.getMinutes()}-${date.getSeconds()}.json`
    const download = document.createElement('a');
    download.setAttribute("href", data);
    download.setAttribute("download", exportTitle);
    document.body.appendChild(download);
    download.click()
    download.remove()
  }

  return (
    <Paper sx={{ padding: 3 }}>
      <h1>Sentiment Analysis Tool</h1>

      <p>Analyzes text content and decided whether the text is positive or negative.</p>
      <p>Choose which model you prefer.</p>
      <p>Besides positive/negative answer, website also displays confidence level</p>
      <Grid container spacing={2}>

        <Grid item xs={6}>
          <TextField
            label="Model"
            select
            value={model}
            onChange={(event) => setModel(event.target.value)}
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
            label="Enter Text for Analysis"
            multiline
            minRows={4}
            fullWidth
            value={inputText}
            onChange={e => setInputText(e.target.value)}
            InputProps={{
              endAdornment: (
                <InputAdornment position="end">
                  <Button variant="contained" size="small" endIcon={<SentimentVerySatisfied />} onClick={handleAnalyze}>
                    Analyze
                  </Button>
                </InputAdornment>
              ),
            }}
          />
          {(analysis !== null) && (
            <Grid container justifyContent="center" sx={{ mt: 4 }}>
              <Grid item xs={12} md={8}>
                <Paper variant="outlined" sx={{ padding: 2 }}>
                  <Typography variant="h5" align="center" gutterBottom>
                    Sentiment: {analysis.toLowerCase() === "positive" ? "Positive" : "Negative"}
                    {analysis.toLowerCase() === "positive" ? (
                      <SentimentVerySatisfied color="success" sx={{ ml: 1 }} />
                    ) : (
                      <SentimentVeryDissatisfied color="error" sx={{ ml: 1 }} />
                    )}
                  </Typography>
                  <Typography variant="h5" align="center" gutterBottom>
                    Score: {score}
                  </Typography>
                  <Grid container justifyContent="center">
                    <Grid item>
                      <Button variant="outlined" onClick={handleExport} startIcon={<SaveIcon />}>
                        Export to JSON
                      </Button>
                    </Grid>
                  </Grid>
                </Paper>
              </Grid>
            </Grid>
          )}
          {isLoading ? <LinearProgress sx={{ mt: 2 }} /> : ""}
        </Grid>
      </Grid>
    </Paper>
  );
}