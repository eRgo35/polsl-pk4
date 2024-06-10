import Copyright from "@/components/Copyright";
import { Container, Grid, Paper, Typography } from "@mui/material";
import DeveloperList from "./DeveloperList";

export const metadata = {
  title: "Developer - NLP Platform"
}

export default function Developer() {
  return (
    <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
      <Grid container spacing={2} justifyContent="center">
        <Grid item xs={12} md={6}>
          <Paper sx={{ padding: 3 }}>
            <Typography variant="h5" sx={{ mb: 2 }}>
              Developer Tools
            </Typography>
            <DeveloperList />
            <br />
          </Paper>
        </Grid>
      </Grid>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}