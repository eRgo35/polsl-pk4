import Copyright from "@/components/Copyright";
import { Container, Grid } from "@mui/material";
import SentimentForm from './Sentiment';

export const metadata = {
  title: "Sentiment Analysis - NLP Platform"
}

export default function Sentiment() {

  return (
    <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <SentimentForm />
        </Grid>
      </Grid>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}