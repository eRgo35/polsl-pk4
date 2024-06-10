import Copyright from "@/components/Copyright";
import TranslateForm from "./Translate";
import { Container, Grid } from "@mui/material";

export const metadata = {
  title: "Machine Translation - NLP Platform"
}

export default function Translate() {
  return (
    <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <TranslateForm />
        </Grid>
      </Grid>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}