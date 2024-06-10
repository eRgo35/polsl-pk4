'use client'
import * as React from 'react';
import { CopyAll, Fingerprint, SentimentVeryDissatisfied, SentimentVerySatisfied } from "@mui/icons-material";
import { Button, Grid, InputAdornment, LinearProgress, Paper, TextField, Typography } from "@mui/material";
import { baseUrl } from '../lib/backend';
import SaveIcon from '@mui/icons-material/Save';

export default function AnonymizationForm() {
  const [inputText, setInputText] = React.useState("");
  const [analysis, setAnalysis] = React.useState(null);
  const [isLoading, setIsLoading] = React.useState(false);

  const handleAnalyze = async () => {
    setIsLoading(true);

    try {
      await fetch(`${baseUrl}/api/anonymize`, {
        method: 'POST',
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json',
          'Authorization': '17e1c9878d714c7f83209cc4084ea632'
        },
        body: JSON.stringify({
          data: inputText
        })
      })
        .then(res => res.json())
        .then(({ data }) => {
          console.log(data)
          setAnalysis(data)
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
    const exportTitle = `anonymization-${date.getFullYear()}-${date.getMonth() + 1}-${date.getDate()}-${date.getHours()}-${date.getMinutes()}-${date.getSeconds()}.json`
    const download = document.createElement('a');
    download.setAttribute("href", data);
    download.setAttribute("download", exportTitle);
    document.body.appendChild(download);
    download.click()
    download.remove()
  }

  const handleCopy = () => {
    return navigator.clipboard.writeText(analysis).then(function () {
      console.log("Copied to clipboard successfully!");
    }, function (err) {
      console.error("Failed to copy to clipboard: ", err);
    });
  }

  return (
    <Paper sx={{ padding: 3 }}>
      <h1>Anonymization Tool</h1>

      <p>Analyzes text content and detects and removes sensitive information.</p>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <TextField
            label="Enter Text to Anonymize"
            multiline
            minRows={4}
            fullWidth
            value={inputText}
            onChange={e => setInputText(e.target.value)}
            InputProps={{
              endAdornment: (
                <InputAdornment position="end">
                  <Button variant="contained" size="small" endIcon={<Fingerprint />} onClick={handleAnalyze}>
                    Anonymize
                  </Button>
                </InputAdornment>
              ),
            }}
          />
          {analysis !== null && (
            <Grid container justifyContent="center" sx={{ mt: 2 }}>
              <TextField
                label="Anonymized Text"
                multiline
                minRows={4}
                fullWidth
                sx={{ mb: 2 }}
                value={analysis}
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