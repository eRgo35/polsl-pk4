import Copyright from "@/components/Copyright";
import { Container, Grid } from "@mui/material";
import AnonymizationForm from './Anonymization';

export const metadata = {
  title: "Anonymization - NLP Platform"
}

export default function Anonymization() {

  return (
    <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <AnonymizationForm />
        </Grid>
      </Grid>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}